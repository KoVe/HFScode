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

    initI2C();
    initRadio();

    unsigned int freq    =  433830000;
    unsigned int step    =      50000;

    setRadio(freq,step);
    runADCautoSampAutoConv();

    return (EXIT_SUCCESS);
}
