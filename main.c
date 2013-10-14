/* 
 * File:   main.c
 * Author: kvheyen
 *
 * Created on August 29, 2013, 10:32 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <plib.h>
#include "buttons.h"
#include "blinkled.h"
#include "config.h"
#include "PWM.h"
#include "I2C.h"
#include "tuner.h"
#include "ADC.h"
#include "demo.h"




void main() {
    SYSTEMConfigPerformance(40000000L);

    initI2C();
    initRadio();
    initADC();
    startPWM(200);
    INTEnableSystemMultiVectoredInt();

    unsigned int freq    = 200000000;
    unsigned int step    =     62500;

    setRadio(freq,step);

    while(1);
}
