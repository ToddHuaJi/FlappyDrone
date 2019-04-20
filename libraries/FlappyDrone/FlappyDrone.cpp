#include "FlappyDrone.h"
#include <ctype.h>
#include <AP_HAL/AP_HAL.h>




FlappyDrone::FlappyDrone(){
    
    fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (fd == 0)
	{
		perror(MODEMDEVICE);
		printf("Failed to open MODEMDEVICE \"/dev/ttyAMA0\"\n");
		exit(-1); 
	}
    dist = 0;
    orientation = 0;
    readSuccess = false;
	set_interface_attribs (fd, BAUDRATE, 0);  // set speed to 19200 bps, 8n1 (no parity)
	set_blocking (fd, 0);                // set no blocking

}



void FlappyDrone::update(){
    readSuccess = false;
    res = read(fd,readout,9);
    uint16_t tempDist = (int)(readout[2]) + (int)(readout[3])*256;
    if(tempDist<1200){
        dist = tempDist;
        readSuccess = true;
    }
    orientation++;
    if(orientation >= 8){
        orientation = 0;
    }

    tcflush(fd,TCIOFLUSH);
}

uint16_t FlappyDrone::max_distance_cm(){
    return max_dist;
}

uint16_t FlappyDrone::min_distance_cm(){
    return min_dist;
}

uint16_t FlappyDrone::distance_cm(){
    return dist;
}

uint16_t FlappyDrone::get_orientation(){
    return orientation;
}

bool FlappyDrone::has_new_data(){
    return readSuccess;
}

void FlappyDrone::flush(){
    tcflush(fd, TCIOFLUSH);
}

int FlappyDrone::set_interface_attribs (int fd, int speed, int parity){
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                printf ("error %d from tcgetattr", errno);
                return -1;
        }

        cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // disable break processing
        tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 0;            // read doesn't block
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
        {
                return -1;
        }
        return 0;    
}

void FlappyDrone::set_blocking (int fd, int should_block){
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (fd, &tty) != 0)
    {
    printf("error %d from tggetattr", errno);
            return;
    }

    tty.c_cc[VMIN]  = should_block ? 1 : 0;
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    if (tcsetattr (fd, TCSANOW, &tty) != 0)
        printf("error %d setting term attributes", errno);

}



