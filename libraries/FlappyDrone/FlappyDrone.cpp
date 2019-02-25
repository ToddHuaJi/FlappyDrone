#include "FlappyDrone.h"
#include <ctype.h>
#include <AP_HAL/AP_HAL.h>
#include <AP_SerialManager/AP_SerialManager.h>



FlappyDrone::FlappyDrone(){
    
    uartPort = new UARTDevice("/dev/ttyAMA0");
    uartPort->set_speed((uint32_t)115200);
    uartPort->open();
}



void FlappyDrone::update(){
    uartPort->read(readout,(uint16_t)9);
}




