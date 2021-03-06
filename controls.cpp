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


//used to pass arguments into the background thread
struct thread_data {
        jetsontx2GPIO STEPS;
        jetsontx2GPIO DIRX;
        int stepdata;
        float initial;
        float final;
};

//background thread function that runs horizontal motors
void *moveXMotor(void* threadarg) {

        //gets the data passed into the thread from the structure using a pointer
        struct thread_data* my_data;
        my_data = (struct thread_data*) threadarg;

        //initialize function variables with data from the structure
        jetsontx2GPIO _DIRX = my_data->DIRX;
        jetsontx2GPIO _STEP = my_data->STEPS;
        const int stepx = 1600;
        float FWDinitial = 8000;
        float FWDfinal = 600;
        float REVinitial = 15000;
        float REVfinal = 400;
        float c0x;
        float highSpeedx;
        int delayx[stepx];
        float lastDelayx = 0;

        //calculates time delays for speed ramping
        if (_DIRX != low) {
                c0x = FWDinitial;
                highSpeedx = FWDfinal;

                for (int j = 0; j < stepx; j++) {
                        float dx = c0x;
                        if (j > 0)
                                dx = lastDelayx - (2 * lastDelayx) / (4 * j + 1);
                        if (dx < highSpeedx)
                                dx = highSpeedx;
                        delayx[j] = dx;
                        lastDelayx = dx;

                }

                // use delays from the array, forward
                for (int j = 0; j < stepx; j++) {
                        gpioSetValue(_STEP, on);
                        usleep(delayx[j]/2);
                        gpioSetValue(_STEP, off);
                        usleep(delayx[j]/2);
                }

                // use delays from the array, backward
                for (int j = 0; j < stepx; j++) {
                        gpioSetValue(_STEP, on);
                        usleep(delayx[stepx - j - 1]/2);
                        gpioSetValue(_STEP, off);
                        usleep(delayx[stepx - j - 1]/2);
                }
        }
        else {
                c0x = REVinitial;
                highSpeedx = REVfinal;

                for (int j = 0; j < stepx; j++) {
                        float dx = c0x;
                        if (j > 0)
                                dx = lastDelayx - (2 * lastDelayx) / (4 * j + 1);
                        if (dx < highSpeedx)
                                dx = highSpeedx;
                        delayx[j] = dx;
                        lastDelayx = dx;

                }

                // use delays from the array, forward
                for (int j = 0; j < stepx; j++) {
                        gpioSetValue(_STEP, on);
                        usleep(delayx[j]/2);
                        gpioSetValue(_STEP, off);
                        usleep(delayx[j]/2);

}

                // use delays from the array, backward
                for (int j = 0; j < stepx; j++) {
                        gpioSetValue(_STEP, on);
                        usleep(delayx[stepx - j - 1]/2);
                        gpioSetValue(_STEP, off);
                        usleep(delayx[stepx - j - 1]/2);
                }
        }


        pthread_exit(NULL);
}

//function to run end effector. Runs on main thread. **** ADD SPRAY CODE HERE ****
void moveEEMotor(jetsontx2GPIO _STEP120, jetsontx2GPIO _ENA120, float IS_EE, float FS_EE) {

        gpioSetValue(_ENA120, on);

        const int stepEE = 285;

        float c0 = IS_EE;
        float highSpeed = FS_EE;
        float lastDelay = 0;

        int delays[stepEE];

        for (int i = 0; i < stepEE; i++) {                              //calculates time delays for speed ramping
                float d = c0;
                if (i > 0)
                        d = lastDelay - (2 * lastDelay) / (4 * i + 1);
                if (d < highSpeed)
                        d = highSpeed;
                delays[i] = d;
                lastDelay = d;

        }

        // use delays from the array, forward
        for (int i = 0; i < stepEE; i++) {
                gpioSetValue(_STEP120, on);
                usleep(delays[i]/2);
                gpioSetValue(_STEP120, off);
                usleep(delays[i]/2);

        }

        // use delays from the array, backward
        for (int i = 0; i < stepEE; i++) {
                gpioSetValue(_STEP120, on);
                usleep(delays[stepEE - i - 1/2]);
                gpioSetValue(_STEP120, off);
                usleep(delays[stepEE - i - 1/2]);

}

        gpioSetValue(_ENA120, off);

}

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
        jetsonTX2GPIONumber step = gpio392; // Output
        jetsonTX2GPIONumber dir = gpio255; // Output
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


int main(int argc, char *argv[]){

        // register signal SIGINT and signal handler
        signal(SIGINT, signalHandler);

        //for FIFO
        float CVspeed=0;
        float CVsize=0;
        bool CVstart=0;
        const char *speedfifo="/tmp/speed";
        const char *sizefifo="/tmp/size";
        const char *startfifo="/tmp/start";

        int steps_x=1250;
        float IS_x=700;
        float FS_x = 700;

        int steps_EE = 285;
        float IS_EE = 30000;
        float FS_EE = 3000;

        //allows access to the stucture in main
        struct thread_data td;


        //thread ID
        pthread_t tid;

        // Create attributes
        pthread_attr_t attr;
        pthread_attr_init(&attr);

        jetsonTX2GPIONumber ENA = gpio396 ;     // Output - xaxis motor
        jetsonTX2GPIONumber STEP = gpio392 ; // Output
        jetsonTX2GPIONumber DIR = gpio255; // Output
        jetsonTX2GPIONumber ENA120 = gpio398;     // Output - EE motors
        jetsonTX2GPIONumber STEP120 = gpio298; // Output
        jetsonTX2GPIONumber DIR120 = gpio389; // Output

        MotorInit(ENA, STEP, DIR);
        MotorInit(ENA120, STEP120, DIR120);

        td.STEPS = STEP;
        td.stepdata = steps_x;
        td.initial = IS_x;
        td.final = FS_x;


        int fdsize = open(sizefifo, O_RDONLY);
        read(fdsize, &CVsize, sizeof(CVsize));
        if(CVsize!=0){
        cout<<"Received:"<<CVsize<<endl;}
        else
        cout<<"none"<<endl;
        close(fdsize);

        int fdspeed = open(speedfifo, O_RDONLY);
        read(fdspeed, &CVspeed, sizeof(CVspeed));
        if(CVspeed!=0){
        cout<<"Received:"<<CVspeed<<endl;}
        else
        cout<<"none"<<endl;
        close(fdspeed);

        int fdstart = open(startfifo, O_RDONLY);
        read(fdstart, &CVstart, sizeof(CVstart));
        if(CVstart!=0){
        cout<<"Received:"<<CVstart<<endl;}
        else
        cout<<"none"<<endl;
        close(fdstart);



                        gpioSetValue(DIR, high);
                        gpioSetValue(DIR120, high);

                        //creates thread to run x-axis motor in one direction
                        pthread_create(&tid, &attr, moveXMotor, &td);

                        //  run EE motor
                        moveEEMotor(STEP120, ENA120, 40000, 4000);

                        //waits until background thread is terminated
                        pthread_join(tid, NULL);

                        gpioSetValue(DIR, low);
                        gpioSetValue(DIR120, low);

                        //creates thread to run x-axis motor in the other direction
                        pthread_create(&tid, &attr, moveXMotor, &td);

                        //run EE motor again
                        moveEEMotor(STEP120, ENA120, 40000, 2000);

                        pthread_join(tid, NULL);

    return 0;
}
