/*
  simple test of UART interfaces
 */

#include <AP_HAL/AP_HAL.h>
#include <AP_HAL_Linux/AP_HAL_Linux.h>
#include <AP_HAL_Linux/UARTDriver.h>
#include <AP_SerialManager/AP_SerialManager.h>
#include <AP_HAL_Linux/HAL_Linux_Class.h>
#include <AP_HAL_Linux/UARTDevice.h>
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

#if HAL_OS_POSIX_IO
#include <stdio.h>

#endif
#define BAUDRATE B115200 
#define MODEMDEVICE "/dev/ttyAMA0"

void setup();
void loop();

int fd;                                                             
    char buf[10];  
	int variable;
	// struct pollfd fds[1];
	int ret, res;

const HAL_Linux::HAL& hal = AP_HAL::get_HAL();
// const AP_HAL::HAL &hal = HAL_Linux::g
// UARTDevice* uartL;
// Linux::UARTDriver *uartDriverTest;

int set_interface_attribs (int fd, int speed, int parity)
{
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

void set_blocking (int fd, int should_block)
{
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


/*
  setup one UART at 57600
 */
static void setup_uart(AP_HAL::UARTDriver *uart, const char *name)
{
    if (uart == nullptr) {
         hal.console->println(name);
        // that UART doesn't exist on this platform
        return;
    }
    
    uart->begin(115200, 0, 0);
    uart->printf("Hello on UART %s \n",
                 name );

    
}


void setup(void)
{
    /*
      start all UARTs at 115200 with default buffer sizes
    */
    hal.scheduler->delay(5000); //Ensure that the uartA can be initialized
    
    setup_uart(hal.uartA, "uartA");  // console
    setup_uart(hal.uartB, "uartB");  // 1st GPS
    setup_uart(hal.uartC, "uartC");  // telemetry 1
    setup_uart(hal.uartD, "uartD");  // telemetry 2
    setup_uart(hal.uartE, "uartE");  // 2nd GPS

    	/* open the device */
	fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (fd == 0)
	{
		perror(MODEMDEVICE);
		printf("Failed to open MODEMDEVICE \"/dev/ttyAMA0\"\n");
		exit(-1); 
	}

	set_interface_attribs (fd, BAUDRATE, 0);  // set speed to 19200 bps, 8n1 (no parity)
	set_blocking (fd, 0);                // set no blocking

  
}

static void test_uart(AP_HAL::UARTDriver *uart, const char *name)
{
    
    uart->printf("Hello on UART %s at %.3f seconds\n",
                 name, (double)(AP_HAL::millis() * 0.001f));
    
    
		

	/* Open STREAMS device. */
	// fds[0].fd = fd;
	// fds[0].events = POLLRDNORM;
    
					res = read(fd,buf,9);
					// buf[res]=0;		// terminate buffer
                    res++;
					// sscanf(buf,"%d\n",&variable);
					uart->printf("Received %x\n",buf[0]);
                    uart->printf("Received %x\n",buf[1]);
                    uart->printf("Received %d\n",(uint8_t)buf[2]);
                    uart->printf("Received %x\n",buf[3]);
                    uart->printf("Received %x\n",buf[4]);
                    uart->printf("Received %x\n",buf[5]);
                    uart->printf("Received %x\n",buf[6]);
                    uart->printf("Received %x\n",buf[7]);
                    uart->printf("Received %x\n",buf[8]);
                    uart->printf("--------");
    tcflush (fd, TCIOFLUSH) ;
	// close(fd);	
	
}




void loop(void)
{
    test_uart(hal.uartA, "uartA");


    // also do a raw printf() on some platforms, which prints to the
    // debug console
#if HAL_OS_POSIX_IO
    ::printf("Hello on debug console at %.3f seconds\n", (double)(AP_HAL::millis() * 0.001f));
#endif

// #if  CONFIG_HAL_BOARD_SUBTYPE == HAL_BOARD_SUBTYPE_LINUX_NAVIO2
//     hal.uartA->set_device_path("/dev/ttyAMA0");
// #endif

    hal.scheduler->delay(100);



}

AP_HAL_MAIN();

