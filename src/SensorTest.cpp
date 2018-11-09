#include <iostream>
#include <pigpio.h>
#include <fstream>

using namespace std;
/*
-----------------------------------------------------
-    This is a standalone working version cpp code   -
-    for TFmini Lidar. Please refer to 11/1 work log -
-    for build                                       -
------------------------------------------------------

*/


int main(int argc, char * argv[]){
    cout << "Hello, World!";

    if (gpioInitialise() < 0)
{
   cout << "GPIO initialisation failed";
   // pigpio initialisation failed.
}
else
{
    /*
    * Reading 2 different safe distance which is specified by user
    * safeDistance[0] is warning distance 
    * safeDistance[1] is dangerous distance
    */
     
    std::fstream myfile("data.txt");
    int safeDistance[2];
    for(int i = 0; i < 2; i++)
    {
        myfile >> safeDistance[i];
       std::cout << safeDistance[i] << "\n";
    }

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
    int count = 0;
    int distance = 0;
    while(1){
	
        /*
        * Each byte have different meaning
        * See TFmini Datasheet for details
        * data[3] is high half of the data
        */

       if(serDataAvailable(ser) == 9 ){
           count ++;
	   serRead(ser, data, 9);
	   if(count > 100){ //use this to set the print out rate
       		
		distance = data[2] + (data[3] * 256);
		//std::cout <<(int)data[0] << " " <<(int)data[1] << " Data is, low and high: ";
           	std::cout << "TFmini reading is : " << distance << "cm \n";
		if(distance < safeDistance[0]){
			std::cout << "This is within warning safeDistance: " << safeDistance[0] << "\n";
			if(distance < safeDistance[1]){
				std::cout << "And it is also within dagenrous safeDistance: " << safeDistance[1] << "\n"; 
			}
		} 
		std::cout << "----------------------------------------------------- \n";
           	count = 0;
	   }
	   data[0]=0x11;
           data[1]=0x22;
           data[2]=0x33;
           data[3]=0x44;
           //std::cout << serDataAvailable(ser) << "\n";
       }
    }

}


    return 0;
}
