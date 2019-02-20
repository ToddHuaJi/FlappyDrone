#include "FlappyDrone.h"
#include <ctype.h>
#include <AP_HAL/AP_HAL.h>
#include <AP_SerialManager/AP_SerialManager.h>



FlappyDrone::FlappyDrone(){
    
    uartPort = new UARTDevice("/dev/ttyAMA0");
    uartPort->set_speed((uint32_t)115200);
    uartPort->open();
}



uint8_t* FlappyDrone::getSingleDistance(){

    uint8_t* output = new uint8_t[10];
    
    uartPort->read(output,(uint16_t)9);
    return output;
}


