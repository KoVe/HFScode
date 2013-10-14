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
#include <math.h>

//#define ADC_CONFIG1     (ADC_SAMP_ON | ADC_FORMAT_SIGN_INT32 | ADC_AUTO_SAMPLING_ON | ADC_CLK_MANUAL)
#define ADC_CONFIG1     (ADC_SAMP_ON | ADC_FORMAT_SIGN_INT32 | ADC_AUTO_SAMPLING_ON | ADC_CLK_TMR)
#define ADC_CONFIG2     (ADC_VREF_AVDD_AVSS | ADC_SAMPLES_PER_INT_4)
#define ADC_CONFIG3     (ADC_CONV_CLK_Tcy2 | ADC_CONV_CLK_PB)
#define ADC_CONFIGSCAN  (SKIP_SCAN_ALL)
#define ADC_CONFIGPORT  (ENABLE_AN3_ANA)


int main() {
    SYSTEMConfigPerformance(SYS_FREQ);
    initADC(ADC_SAMPLES_PER_INT_1);

    int ADCValues[4];
    int ADCValuesCnt=0;
    int prod[2];
    int ampl;

    startPWM(10);
    mPORTBSetPinsDigitalOut(BIT_6);

    while(1)
    {
        while(!BusyADC10());
        ADCValues[ADCValuesCnt] = ReadADC10(0);

        prod[ADCValuesCnt%2] = (ADCValues[ADCValuesCnt%2]-ADCValues[(ADCValuesCnt%2) +2 ])*(ADCValues[ADCValuesCnt%2]-ADCValues[(ADCValuesCnt%2) +2 ]);
        
        ampl = prod[0]+prod[1];
        ampl = (int) (sqrt(ampl)+0.5);
        ampl = (ampl << 6) >> (10);
        ampl = (ampl>64)?64:ampl;
        ampl = (ampl<0)?0:ampl;

        setPWM(ampl);
//        if(ampl>0x1FF)
//            mPORTBSetBits(BIT_6);
//        else
//            mPORTBClearBits(BIT_6);
        ADCValuesCnt = (ADCValuesCnt+1) % 4;




    }

    return (EXIT_SUCCESS);
}
