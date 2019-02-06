#include "FlappyDrone.h"
#include <ctype.h>
#include <AP_HAL/AP_HAL.h>
#include <AP_SerialManager/AP_SerialManager.h>
#include <stdint.h>
#include <AP_HAL_Linux/UARTDriver.h> 


FlappyDrone::FlappyDrone(AP_SerialManager &_serial_manager){
    uartDriver = UARTDriver(true);
    uartDriver.set_device_path("/dev/ttyAMA0");
    uartDriver.begin(115200);
    
}
void setup(){
    // if(TFminiDriver == nullptr){
        
    // }
    // hal.scheduler->delay(1000);
    // TFminiDriver->begin(115200);
}
// void FlappyDrone::init(void){
//     // if(num_instance!=0){
//     //     return;
//     }

int FlappyDrone::get_reading(){
    if(uartDriver==nullptr){
        return false;
    }
    if(!uartDriver.is_active){
        return false;
    }
    int sum =0;
    uint16_t count = 0;
    uint16_t nbytes = uartDriver->available();
    return (int)nbytes;
    while(nbytes-- > 0){
        char c = uartDriver->read();
        // return (int)c;
        count++;
        if(count == 3){ //first data char
            sum += (uint16_t)c;
        }
        if(count == 4){ //second data char 
            sum += 256*((uint16_t)c);
        }
    }

    if(count == 0){
        return -1;
    }
    return sum;
}


