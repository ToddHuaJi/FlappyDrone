//
// Created by Conley on 1/23/2019.
//

#ifndef DRIVER_MUX_H
#define DRIVER_MUX_H
#include "gpio.h"

class Mux {
public:
    Mux();
    bool initializeGpio();
    void setChannel(int channel);
    int getDistanceData(unsigned ser);

private:
    Navio::Pin *pinE;
    Navio::Pin *pin0;
    Navio::Pin *pin1;
    Navio::Pin *pin2;
    Navio::Pin *pin3;
};



#endif //DRIVER_MUX_H
