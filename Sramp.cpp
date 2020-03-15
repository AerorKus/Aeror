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

void MotorInit(jetsontx2GPIO _ENA, jetsontx2GPIO _STEP, jetsontx2GPIO _DIR) {

        cout << "exporting pins" << endl;
        // Make the button and led available in user space
        gpioExport(_ENA);
        gpioExport(_DIR);
        gpioExport(_STEP);
        gpioSetDirection(_ENA, outputPin);
        gpioSetDirection(_DIR, outputPin);
        gpioSetDirection(_STEP, outputPin);
        gpioSetValue(_ENA, high);

}

void signalHandler(int signum) {
        cout << "Disabling motors\n";

        // cleanup and close up stuff here
        // terminate program
        jetsonTX2GPIONumber ena = gpio396;     // Output - xaxis motors
        jetsonTX2GPIONumber step = gpio466; // Output
        jetsonTX2GPIONumber dir = gpio397; // Output
        jetsonTX2GPIONumber ena120 = gpio398;     // Output - EE motors
        jetsonTX2GPIONumber step120 = gpio298; // Output
        jetsonTX2GPIONumber dir120 = gpio389; // Output

        gpioSetValue(ena, low);
        gpioSetValue(dir, low);
        gpioSetValue(step, low);
        gpioSetValue(ena120, low);
        gpioSetValue(dir120, low);
        gpioSetValue(step120, low);

        gpioUnexport(ena);     // unexport the ENA
        gpioUnexport(dir);      // unexport the DIR
        gpioUnexport(step);      // unexport the STEP
        gpioUnexport(ena120);     // unexport the ENA
        gpioUnexport(dir120);      // unexport the DIR
        gpioUnexport(step120);      // unexport the STEP
        exit(signum);
}

int main(){  
		signal(SIGINT, signalHandler);
		jetsonTX2GPIONumber ENA = gpio396;
		jetsonTX2GPIONumber DIR = gpio466;
		jetsonTX2GPIONumber STEP = gpio397;
		
		MotorInit(ENA, STEP, DIR);

		float d=0.5,v=0,v_CV=10,delay,time=0,ta=0,a=0,linear_length,time_total,curve_ratio,linear_ratio=0.75;
        float sarray[1000000];

        time_total=d*100/v_CV;
        curve_ratio=(1-linear_ratio)/4;
        ta=2*curve_ratio*time_total;

        int s=0;
		
		gpioSetValue(DIR,on);
		gpioSetValue(ENA,on);
        while(time<ta){
                if(time<=ta/2)
                        v=a*a/(2*v_CV)*time*time;
                else if(time>(ta/2)&&time<=ta)
                        v=a*a/(2*v_CV)*(ta-time)*(ta-time);

                delay=0.00403/v;
                sarray[s]=delay;
                time=time+delay;
                cout<<sarray[s]<<endl;
                s++;
        }
        size_t n = sizeof(sarray);
        cout<<"size of array="<<n<<endl;

        for(int i=0;i<n;i++){
                gpioSetValue(STEP,on);
                usleep(sarray[i]/2);
                gpioSetValue(STEP,off);
                usleep(sarray[i]/2);
        }
return 0;
}