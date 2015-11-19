#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS_DriverInterface.h"

typedef struct
{

}s_DRIVER;

int main()
{
    Peripheral_Control_t dev;
    printf("Hello world!\n");


    DRIVER_LoadAll();

    dev.pxDevice.pcPath = "GPIO0";
    DRIVER_Add(&dev);







    DRIVER_open("GPIO0",0);








    return 0;
}
