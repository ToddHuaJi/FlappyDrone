#include "FlappyDrone.h"
#include <ctype.h>
#include <AP_HAL/AP_HAL.h>
#include <AP_SerialManager/AP_SerialManager.h>

// const AP_HAL::HAL& hal = AP_HAL::get_HAL();

FlappyDrone::FlappyDrone(AP_SerialManager &serial_manager){
    
    uart = serial_manager.find_serial(serial_manager.SerialProtocol_Rangefinder,0);

}

void setup(){
    
}

int FlappyDrone::get_reading(){

    int sum =0;
    uint16_t count = 0;
    uint16_t nbytes =  uart->available();
    return (int)nbytes;
    while(nbytes-- > 0){
        char c =  uart->read();
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


