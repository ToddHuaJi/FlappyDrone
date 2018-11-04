#include <iostream>
#include <pigpio.h>

using namespace std;
/*
------------------------------------------------------
-    This is a standalone working version cpp code   -
-    for TFmini Lidar. Please refer to 11/1 work log -
-    for build                                       -
------------------------------------------------------

*/


int main(){
    cout << "Hello, World!";

    if (gpioInitialise() < 0)
{
   cout << "GPIO initialisation failed";
   // pigpio initialisation failed.
}
else
{

    /*
    * sepcifing Serial port path in string and convert
    * into char array. serOpen hates strings
    * 
    */
    std::string s = "/dev/ttyAMA0";
    char cstr[s.size() + 1];
    std::copy(s.begin(), s.end(), cstr);
    cstr[s.size()]='\0';

    /*
    * opening serial communication port
    * @Param
    *   cstr: port path
    *   115200: Baud rate
    *   0: serFlags, 0 is ok
    */
    unsigned ser = serOpen(cstr,115200, 0);
    char data[9];

    while(1){

        /*
        * Each byte have different meaning
        * See TFmini Datasheet for details
        * data[3] is high half of the data
        */

       if(serDataAvailable(ser) == 9 ){
           serRead(ser, data, 9);
           std::cout <<(int)data[0] << " " <<(int)data[1] << " Data is, low and high: ";
           std::cout <<(int)data[2] << " " <<(int)data[3] << " +++ \n";
           data[0]=0x11;
           data[1]=0x22;
           data[2]=0x33;
           data[3]=0x44;
           std::cout << serDataAvailable(ser) << "\n";
       }
    }

}


    return 0;
}