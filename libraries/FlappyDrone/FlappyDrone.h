/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */



#pragma once

#include <AP_Common/AP_Common.h>
#include <AP_HAL/AP_HAL.h>
#include <AP_Param/AP_Param.h>
#include <AP_Math/AP_Math.h>
#include <AP_SerialManager/AP_SerialManager.h>
#include <stdint.h>
#include <AP_HAL_Linux/UARTDriver.h>

class FlappyDrone{
      
public:
  

    FlappyDrone(AP_SerialManager &serial_manager);
  
    static bool detect(AP_SerialManager &serial_manager, uint8_t serial_instance);

    int get_reading();
    void setup();
   
private:
    AP_HAL::UARTDriver *uart = nullptr;
    char databuf[9];
};

