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
#include <termios.h>                                                         
#include <stdio.h>
#include <stdlib.h>	
#include <string.h>
#include <unistd.h>                                                          
#include <fcntl.h>                                                                                                               
#include <sys/types.h> 
#include <stdint.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <stdbool.h>
#include <stropts.h>
#include <poll.h>	

#include <errno.h>


#define BAUDRATE B115200 
#define MODEMDEVICE "/dev/ttyAMA0"

/*
    AP_HAL is completely ignored
*/
class FlappyDrone{
      
public:

    unsigned char* readout = new unsigned char[10];
    uint64_t fd;

    FlappyDrone();
    void update();
    // uint8_t* getReading();
    /*flush is doing what flush does*/
    void flush();
    
   
private:
    
    int set_interface_attribs (int fd, int speed, int parity);
    void set_blocking (int fd, int should_block);

    int res;
    
};

