#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include <cmath>
#include <csignal>
#include "jetsontx2GPIO.h"
using namespace std;


void signalHandler(int signum){
       jetsonTX2GPIONumber gpio1=gpio396;	
       jetsonTX2GPIONumber gpio2=gpio466;
       jetsonTX2GPIONumber gpio3=gpio397;
       jetsonTX2GPIONumber gpio4=gpio255;
       jetsonTX2GPIONumber gpio5=gpio429;
       jetsonTX2GPIONumber gpio6=gpio428;
       jetsonTX2GPIONumber gpio7=gpio427;
       jetsonTX2GPIONumber gpio8=gpio398;
       jetsonTX2GPIONumber gpio9=gpio298;
       jetsonTX2GPIONumber gpio10=gpio389;
       jetsonTX2GPIONumber gpio11=gpio395;
       jetsonTX2GPIONumber gpio12=gpio388;
       jetsonTX2GPIONumber gpio13=gpio392;
       jetsonTX2GPIONumber gpio14=gpio296;
       jetsonTX2GPIONumber gpio15=gpio481;
       jetsonTX2GPIONumber gpio16=gpio254;
       jetsonTX2GPIONumber gpio17=gpio430;
       jetsonTX2GPIONumber gpio18=gpio297;
       jetsonTX2GPIONumber gpio19=gpio467;
       jetsonTX2GPIONumber gpio20=gpio394;
       jetsonTX2GPIONumber gpio21=gpio393;
	   
        gpioSetValue(gpio1, low);
		gpioSetValue(gpio2, low);
		gpioSetValue(gpio3, low);
		gpioSetValue(gpio4, low);
		gpioSetValue(gpio5, low);
		gpioSetValue(gpio6, low);
		gpioSetValue(gpio7, low); 
		gpioSetValue(gpio8, low);
		gpioSetValue(gpio9, low);
		gpioSetValue(gpio10, low);
		gpioSetValue(gpio11, low);
		gpioSetValue(gpio12, low);
		gpioSetValue(gpio13, low);
		gpioSetValue(gpio14, low);
		gpioSetValue(gpio15, low);
		gpioSetValue(gpio16, low);
		gpioSetValue(gpio17, low);
		gpioSetValue(gpio18, low);
		gpioSetValue(gpio19, low);
		gpioSetValue(gpio20, low);
		gpioSetValue(gpio21, low);
	
        gpioUnexport(gpio1);
		gpioUnexport(gpio2);
		gpioUnexport(gpio3);
		gpioUnexport(gpio4);
		gpioUnexport(gpio5);
		gpioUnexport(gpio6);
		gpioUnexport(gpio7);
		gpioUnexport(gpio8);
		gpioUnexport(gpio9);
		gpioUnexport(gpio10);
		gpioUnexport(gpio11);
		gpioUnexport(gpio12);
		gpioUnexport(gpio13);
		gpioUnexport(gpio14);
		gpioUnexport(gpio15);
		gpioUnexport(gpio16);
		gpioUnexport(gpio17);
		gpioUnexport(gpio18);
		gpioUnexport(gpio19);
		gpioUnexport(gpio20);
		gpioUnexport(gpio21);
exit(signum);	
}

int main(){
signal(SIGINT,signalHandler);

       jetsonTX2GPIONumber gpio1=gpio396;	
       jetsonTX2GPIONumber gpio2=gpio466;
       jetsonTX2GPIONumber gpio3=gpio397;
       jetsonTX2GPIONumber gpio4=gpio255;
       jetsonTX2GPIONumber gpio5=gpio429;
       jetsonTX2GPIONumber gpio6=gpio428;
       jetsonTX2GPIONumber gpio7=gpio427;
       jetsonTX2GPIONumber gpio8=gpio398;
       jetsonTX2GPIONumber gpio9=gpio298;
       jetsonTX2GPIONumber gpio10=gpio389;
       jetsonTX2GPIONumber gpio11=gpio395;
       jetsonTX2GPIONumber gpio12=gpio388;
       jetsonTX2GPIONumber gpio13=gpio392;
       jetsonTX2GPIONumber gpio14=gpio296;
       jetsonTX2GPIONumber gpio15=gpio481;
       jetsonTX2GPIONumber gpio16=gpio254;
       jetsonTX2GPIONumber gpio17=gpio430;
       jetsonTX2GPIONumber gpio18=gpio297;
       jetsonTX2GPIONumber gpio19=gpio467;
       jetsonTX2GPIONumber gpio20=gpio394;
       jetsonTX2GPIONumber gpio21=gpio393;
	   
        gpioExport(gpio1);
		gpioExport(gpio2);
		gpioExport(gpio3);
		gpioExport(gpio4);
		gpioExport(gpio5);
		gpioExport(gpio6);
		gpioExport(gpio7);
		gpioExport(gpio8);
		gpioExport(gpio9);
		gpioExport(gpio10);
		gpioExport(gpio11);
		gpioExport(gpio12);
		gpioExport(gpio13);
		gpioExport(gpio14);
		gpioExport(gpio15);
		gpioExport(gpio16);
		gpioExport(gpio17);
		gpioExport(gpio18);
		gpioExport(gpio19);
		gpioExport(gpio20);
		gpioExport(gpio21);
		
		gpioSetDirection(gpio1, outputPin);
		gpioSetDirection(gpio2, outputPin);
		gpioSetDirection(gpio3, outputPin);
		gpioSetDirection(gpio4, outputPin);
		gpioSetDirection(gpio5, outputPin);
		gpioSetDirection(gpio6, outputPin);
		gpioSetDirection(gpio7, outputPin);
		gpioSetDirection(gpio8, outputPin);
		gpioSetDirection(gpio9, outputPin);
		gpioSetDirection(gpio10, outputPin);
		gpioSetDirection(gpio11, outputPin);
		gpioSetDirection(gpio12, outputPin);
		gpioSetDirection(gpio13, outputPin);
		gpioSetDirection(gpio14, outputPin);
		gpioSetDirection(gpio15, outputPin);
		gpioSetDirection(gpio16, outputPin);
		gpioSetDirection(gpio17, outputPin);
		gpioSetDirection(gpio18, outputPin);
		gpioSetDirection(gpio19, outputPin);
		gpioSetDirection(gpio20, outputPin);
		gpioSetDirection(gpio21, outputPin);

		gpioSetValue(gpio1, high);
		gpioSetValue(gpio2, high);
		gpioSetValue(gpio3, high);
		gpioSetValue(gpio4, high);
		gpioSetValue(gpio5, high);
		gpioSetValue(gpio6, high);
		gpioSetValue(gpio7, high);
		gpioSetValue(gpio8, high);
		gpioSetValue(gpio9, high);
		gpioSetValue(gpio10, high);
		gpioSetValue(gpio11, high);
		gpioSetValue(gpio12, high);
		gpioSetValue(gpio13, high);
		gpioSetValue(gpio14, high);
		gpioSetValue(gpio15, high);
		gpioSetValue(gpio16, high);
		gpioSetValue(gpio17, high);
		gpioSetValue(gpio18, high);
		gpioSetValue(gpio19, high);
		gpioSetValue(gpio20, high);
		gpioSetValue(gpio21, high);
		
signal(SIGINT,signalHandler);
		
		
		
return 0;
}


       
       

