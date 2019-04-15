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

#include <AP_HAL/AP_HAL.h>
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
#include <AP_HAL/AP_HAL.h>
#include <errno.h>

#define HAL_GPIO_OUTPUT 1
#define BAUDRATE B115200
#define MODEMDEVICE "/dev/ttyAMA0"
//extern const AP_HAL::HAL& hal;
/*
    AP_HAL is completely ignored
*/
class FlappyDrone{

public:

    unsigned char* readout = new unsigned char[10];
   // unsigned char** allSensorData = new unsigned char[9][10];
    unsigned char** allSensorData ;  // array of pointers, c points to first element
    uint16_t* caculatedDistances;
    int* distanceTimeStamp;

    int SwitchSensor( const AP_HAL::HAL& hal);
    int sensorNumber = 0;
    bool isInit = false;
    uint16_t min_dist = 30;
    uint16_t max_dist = 1200;
    uint64_t fd;
    uint16_t dist;  // calculated distance, range: [30,1200], current sensor reading
    uint16_t orientation;
    bool readSuccess;


    FlappyDrone();
    void update();      // single update
    uint16_t max_distance_cm();
    uint16_t min_distance_cm();
    uint16_t distance_cm();
    uint16_t get_orientation();
    bool has_new_data();

    // uint8_t* getReading();
    /*flush is doing what flush does*/
    void flush();



private:

    int set_interface_attribs (int fd, int speed, int parity);
    void set_blocking (int fd, int should_block);



};
