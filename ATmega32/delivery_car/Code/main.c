#include "APP/APP.h"

int main()
{
	APP_Init();

	APP_main_loop();
	while(1);

	return 0;
}

