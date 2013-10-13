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
    //demoButton();
    //demoI2C();
    //demoTuner();
    demoADC();
    
}
