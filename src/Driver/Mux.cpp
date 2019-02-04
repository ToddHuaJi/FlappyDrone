//
// Created by Conley on 1/23/2019.
//

#include "Mux.h"
#include <iostream>
#include <pigpio.h>
#include <fstream>

#define HI 1
#define LO 0
using namespace Navio;

Mux::Mux(){

}

bool Mux::initializeGpio(){
    pinE = new Pin(RPI_GPIO_27);
    pin0 = new Pin(RPI_GPIO_28);
    pin1 = new Pin(RPI_GPIO_29);
    pin2 = new Pin(RPI_GPIO_30);
    pin3 = new Pin(RPI_GPIO_31);
    if (pinE->init() && pin0->init() && pin1->init() && pin2->init() && pin3->init()) {
        pinE->setMode(Pin::GpioModeOutput);
        pin0->setMode(Pin::GpioModeOutput);
        pin1->setMode(Pin::GpioModeOutput);
        pin2->setMode(Pin::GpioModeOutput);
        pin3->setMode(Pin::GpioModeOutput);


        // Switch off Mux
        pinE->write(LO);
        pin0->write(HI);
        pin1->write(HI);
        pin2->write(HI);
        pin3->write(HI);

    }
    else {
        return false;
    }
    return true;
}

// return distance if data available else return -1;   need to do SerOpen first and maybe flash first
int Mux::getDistanceData(unsigned ser){

    char data[9];
    int count = 0;
    int distance = 0;
    if(serDataAvailable(ser) == 9 ){
        serRead(ser, data, 9);
        distance = data[2] + (data[3] * 256);
        //std::cout <<(int)data[0] << " " <<(int)data[1] << " Data is, low and high: ";
        std::cout << "TFmini reading is : " << distance << "cm \n";
        return distance;
            //std::cout << serDataAvailable(ser) << "\n";
    }
    return -1;
}

void Mux::setChannel(int channel){
    pinE->write(HI);
    switch (channel) {
        // trivial , need to be defined
        case 0: pin0->write(OFF); pin1->write(OFF); pin2->write(OFF); pin3->write(OFF);break;
        case 1: pin0->write(OFF); pin1->write(OFF); pin2->write(OFF); pin3->write(OFF);break;
        case 2: pin0->write(OFF); pin1->write(OFF); pin2->write(OFF); pin3->write(OFF);break;
        case 3: pin0->write(OFF); pin1->write(OFF); pin2->write(OFF); pin3->write(OFF);break;
        case 4: pin0->write(OFF); pin1->write(OFF); pin2->write(OFF); pin3->write(OFF);break;
        case 5: pin0->write(OFF); pin1->write(OFF); pin2->write(OFF); pin3->write(OFF);break;
        case 6: pin0->write(OFF); pin1->write(OFF); pin2->write(OFF); pin3->write(OFF);break;
        case 7: pin0->write(OFF); pin1->write(OFF); pin2->write(OFF); pin3->write(OFF);break;
        case 8: pin0->write(OFF); pin1->write(OFF); pin2->write(OFF); pin3->write(OFF);break;
        case 9: pin0->write(OFF); pin1->write(OFF); pin2->write(OFF); pin3->write(OFF);break;
    }
}
