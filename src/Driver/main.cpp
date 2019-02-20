#include <iostream>
#include <pigpio.h>
#include <fstream>
#include "gpio.h"
#include "Mux.h"
#include "Mux.cpp"
#include "gpio.cpp"
#include <iostream>

int main(int argc, char* argv[]){
	//Pin *pin7 = new Pin(RPI_GPIO_18);
	Mux *mux = new Mux();
	    if (gpioInitialise() < 0)
{
   //cout << "GPIO initialisation failed";
   // pigpio initialisation failed.
}
	std::string s = "/dev/ttyAMA0";
    char cstr[s.size() + 1];
    std::copy(s.begin(), s.end(), cstr);
    cstr[s.size()]='\0';
    unsigned ser = serOpen(cstr,115200, 0);
    
    
	//printf("%d\n",mux->initializeGpio());
	if(mux->initializeGpio()){
		mux->setChannel(0);
		while(1){
		printf("%d\n",mux->getDistanceData(ser));
		
	}
	}
	
	
	
	//mux->getDistanceData()
	//if(pin7->init()){
	//	pin7 ->setMode(Pin::GpioModeOutput);
	//	pin7 ->write(1);
	//}
	
	return 0;
	
		
}
