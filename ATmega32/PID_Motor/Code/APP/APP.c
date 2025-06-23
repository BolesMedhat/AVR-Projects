/****************************************************************************
 * @file    APP.c
 * @author  Boles Medhat
 * @brief   PID Motor Control Application - ATmega32
 * @version 1.0
 * @date    [2024-05-20]
 *
 * @details
 * This application implements a real-time PID control loop using the ATmega32
 * microcontroller to control the speed or position of a DC motor. The control
 * system supports both digital and analog modes:
 *
 * - In **digital mode**, the user is prompted through UART to enter the Kp, Ki,
 *   and Kd values manually, and a desired setpoint. This is ideal for testing
 *   and real-time tuning over serial.
 *
 * - In **analog mode**, PID constants and setpoint are read from ADC channels,
 *   making the system fully autonomous. Analog mode is selected by default
 *   if no user input is received within 5 seconds.
 *
 * The control loop runs periodically using TIMER2 interrupts. The PID output
 * is applied to a DC motor using PWM via TIMER0, and direction control is
 * managed through DIO. The resulting control signal is also output via PORTC
 * for DAC-based visualization (e.g., using an R-2R ladder).
 *
 * Features:
 * - PID controller with anti-oscillation deadband
 * - UART-based user interaction
 * - Real-time ADC-based gain and setpoint input
 * - Motor direction and PWM control
 * - Optional DAC output for debugging
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/


#include "APP.h"



// ======================================
// Global Variables
// ======================================
float64 kp;
float64 ki;
float64 kd;
sint16 setpoint = 0;
sint16 position = 0;
sint16 last_position = 0;
sint16 error = 0;
sint16 prev_error = 0;
double proportional = 0;
double integral = 0;
double derivative = 0;
const double dt = SAMPLE_MS / 1000.0;
sint16 output = 0;
uint16 timer_overflows;
uint8 timer_initval;
bool is_digital;
Motor motor = { MOTOR_PORT, MOTOR_IN1, MOTOR_IN2 };



int abs(int x)
{
    return (x < 0) ? -x : x;
}





/*
 * @brief Prompts the user to select digital mode via UART.
 *
 * Waits up to 5 seconds after ask user for a user response. If 'y' or 'Y' is
 * received, digital mode is enabled. Otherwise, analog mode is used by default.
 *
 * @return true if digital mode is selected, false otherwise.
 */
bool Is_Use_UART()
{
	uint8 count = 0;
	bool is_digital = false;

	/* Initial delay to allow the user to open the serial terminal */
	_delay_ms(2000);

	/* Prompt the user to choose digital mode via UART */
	UART_WriteString("Use digital values?[y/n]\n");

	/* Wait for up to 5 seconds (25 × 200ms) for user input */
	while(count < 25)
	{
		/* Check if UART input is available */
		if(UART_IsAvailableToRead())
		{
			char input[10];

			/* Read user input */
			UART_ReadStringUntil(input, STOP_CHAR);

			/* If user inputs 'y' or 'Y', select digital mode */
			if( input[0] == 'y' || input[0] == 'Y' )
			{
				is_digital = true;
				break;
			}
			/* Any other input defaults to analog mode */
			else
			{
				break;
			}
		}

		/* Increment wait counter and delay */
		count++;
		_delay_ms(200);
	}

	/* Return mode selection result */
	return is_digital;
}





/*
 * @brief Reads PID constants (Kp, Ki, Kd) from UART input.
 *
 * Continuously prompts the user for Kp, Ki, and Kd values until they confirm the input.
 *
 * @param[out] kp_value Pointer to store the proportional gain.
 * @param[out] ki_value Pointer to store the integral gain.
 * @param[out] kd_value Pointer to store the derivative gain.
 */
void Get_k_Values( float64 * kp_value , float64 * ki_value , float64 * kd_value )
{
	char k_value[10];
	char input[10];

	while(1)
	{
		/* Prompt user to enter Kp value and convert from string to float */
		UART_WriteString("Enter Kp value:\n");
		UART_ReadStringUntil(k_value, STOP_CHAR);
		*kp_value = DC_atof(k_value);

		/* Prompt user to enter Ki value and convert from string to float */
		UART_WriteString("Enter Ki value:\n");
		UART_ReadStringUntil(k_value, STOP_CHAR);
		*ki_value = DC_atof(k_value);

		/* Prompt user to enter Kd value and convert from string to float */
		UART_WriteString("Enter Kd value:\n");
		UART_ReadStringUntil(k_value, STOP_CHAR);
		*kd_value = DC_atof(k_value);

		/* Display the entered PID values for confirmation */
		UART_WriteString("kp = ");
		UART_WriteFloat(*kp_value,3);

		UART_WriteString(",ki = ");
		UART_WriteFloat(*ki_value,3);

		UART_WriteString(",kd = ");
		UART_WriteFloat(*kd_value,3);

		/* Ask user to confirm if the entered values should be used */
		UART_WriteString("\nUse this values?[y/n]\n");
		UART_ReadStringUntil(input, STOP_CHAR);

		/* If confirmed, exit the loop; otherwise, re-enter values */
		if( input[0] == 'y' || input[0] == 'Y' )
		{
			break;
		}

	}
}





/*
 * @brief Drives the motor based on the given signed speed.
 *
 * Sets direction and PWM duty cycle using Timer0.
 *
 * @param[in] speed Signed motor speed (-255 to 255).
 */
void Motor_Drive(sint16 speed)
{

	/* Set motor direction based on sign of speed */
	if (speed > 0)
	{
		/* Forward direction */
		MOTOR_Forward(motor);
	}
	else if (speed < 0)
	{
		/* Backward direction */
		MOTOR_Backward(motor);
	}
	else
	{
		/* Stop the motor if speed is zero */
		MOTOR_Stop(motor);
	}

	/* Set PWM duty cycle using absolute value of speed */
	TIMER0_SetCompareValue(abs(speed));
}





/*
 * @brief Performs PID computation and updates motor control output.
 *
 * Reads feedback (and optionally setpoint and PID gains in analog mode),
 * computes the PID output, clamps it, and drives the motor accordingly.
 * Also updates a DAC output for visualization.
 */
void PID_Update()
{

	/* Read the current position (feedback) from ADC channel */
	position = ADC_Read_10_Bits(FEEDBACK_ADC);   // 0 to 1023

	/* In analog mode: read setpoint and PID gains from ADC inputs */
	if (is_digital == false)
	{
		/* Target position */
		setpoint = ADC_Read_10_Bits(SETPOINT_ADC);

		/* Scale ADC readings to real gain values (based on defined max) */
		kp = ( ADC_Read_10_Bits(KP_ADC) * KP_MAX ) / 1023.0;
		ki = ( ADC_Read_10_Bits(KI_ADC) * KI_MAX ) / 1023.0;
		kd = ( ADC_Read_10_Bits(KD_ADC) * KD_MAX ) / 1023.0;
	}

	/* Calculate current control error */
	error = setpoint - position;

	/* Deadband: ignore small errors to prevent oscillation */
	if (abs(error) < DEADBAND)
	{
		/* Reset integral to avoid wind-up */
		integral = 0;
		output = 0;
	}
	/* PID calculations */
	else
	{
		/* Proportional term */
		proportional = kp * error;

		/* Accumulate integral term */
		integral += ki * error * dt;

		/* Derivative based on position change */
		derivative = kd * (last_position - position) / dt;

		/* Compute total output */
		output = proportional + integral + derivative;

		/* Clamp output to PWM range (-255 to 255) */
		if (output > 255)
		{
			output = 255;
		}
		else if (output < -255)
		{
			output = -255;
		}
	}

	/* Save current position for next derivative calculation */
	last_position = position;

	/* Drive the motor based on signed output */
	Motor_Drive(output);

	/* Absolute value is sent to DAC output for visualization */
	DIO_SetPortValue(DAC_PORT, (uint8)abs(output));
}





/*
 * @brief Timer2 overflow interrupt service routine callback.
 *
 * Counts overflows until the configured sampling interval elapses,
 * then resets the timer and triggers a PID update.
 */
void Control_ISR()
{
	static uint16 ovf_counter = 0;

	/* Increment overflow counter on each TIMER2 overflow interrupt */
	if (++ovf_counter >= timer_overflows)
	{
		/* Reset counter when target time is reached (e.g. 20 ms) */
		ovf_counter = 0;

		/* Reload TIMER2 with initial value for consistent timing */
		TIMER2_SetTimerValue(timer_initval);

		/* Call PID update routine to compute control output */
		PID_Update();
	}
}





/*
 * @brief Initializes the main application modules.
 *
 * This function sets up UART, ADC, motor control, timers, and ISR configuration.
 * It determines whether to use digital or analog mode and prepares everything for PID control.
 */
void APP_Init(void)
{
	/* Initialize UART for communication */
	UART_Init();

	/* Initialize motor control pins */
	MOTOR_Init(motor);

	/* Initialize ADC for reading feedback, setpoint, and PID gains */
	ADC_Init();

	/* Check if digital mode is selected via UART (within 5 seconds) */
	is_digital = Is_Use_UART();

	/* If digital mode is selected, get Kp, Ki, Kd from user input */
	if(is_digital == true)
	{
		Get_k_Values(&kp,&ki,&kd);
	}

	/* Initialize Timer0 for PWM generation (motor speed control) */
	TIMER0_Init();

	/* Initialize Timer2 for periodic PID control ISR */
	TIMER2_Init();

	/* Set direction to output for DAC visualization (R-2R ladder) */
	DIO_SetPortDirection(DAC_PORT, OUTPUT_PORT);

	/* Calculate overflow count and preload value for TIMER2 to match sample time */
	TIMER2_Calc_ISR_Timing_ms(SAMPLE_MS, &timer_overflows, &timer_initval);

	/* Set initial timer value for TIMER2 */
	TIMER2_SetTimerValue(timer_initval);

	/* Set the PID control function to be called on TIMER2 overflow interrupt */
	TIMER2_SetCallback(TIMER2_OVF_ID, Control_ISR);
}





/*
 * @brief Main application loop for user interaction and system monitoring.
 *
 * Continuously monitors system state and handles UART interaction for setpoint input or status reporting.
 * In digital mode, displays error and PID constants when a significant change occurs.
 * In analog mode, continuously prints system status.
 */
void APP_main_loop(void)
{
	char input[10];
	sint16 temp;

	/* Control is interrupt-based; loop only handles UART interaction */
	while(1)
	{
		/* If digital mode is selected */
		if (is_digital == true)
		{
			/* If error changes significantly, display PID data */
			if (abs(error - prev_error) > DEADBAND )
			{
				UART_WriteString("Error = ");
				UART_WriteNumber(error);
				UART_WriteByte('\n');
				prev_error = error;

				UART_WriteString("Kp = ");
				UART_WriteFloat(kp,3);

				UART_WriteString(",Ki = ");
				UART_WriteFloat(ki,3);

				UART_WriteString(",Kd = ");
				UART_WriteFloat(kd,3);
				UART_WriteString("\n\n");
			}
			/* If error is within the deadband, prompt user to enter new setpoint */
			else if(abs(error) < DEADBAND)
			{
				while(1)
				{
					UART_WriteString("Enter set point:\n");

					UART_ReadStringUntil(input, STOP_CHAR);
					temp = DC_atoi(input);

					/* Accept valid setpoints within ADC range */
					if(temp < 1024)
					{
						setpoint = temp;
						break;
					}
					else
					{
						UART_WriteString("Invalid set point range is from 0 to 1023\n");
					}
				}


			}
		}
		/* In analog mode: continuously report system status over UART */
		else
		{
			UART_WriteString("Setpoint:");
			UART_WriteNumber(setpoint);
			UART_WriteByte(',');
			UART_WriteString("Position:");
			UART_WriteNumber(position);
			UART_WriteByte(',');
			UART_WriteString("Error:");
			UART_WriteNumber(error);
			UART_WriteString("\r\n");
		}
		/* Small delay to limit UART flooding */
		_delay_ms(100);

	}
}
