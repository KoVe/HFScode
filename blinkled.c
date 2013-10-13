#include "blinkled.h"
#include <plib.h>

/* Two functions to make a led at RPB7 (pin16) blink. These functions can be
 * used for debugging. Important they never return, contain while(1)
 */

void fadeLed(int max){
    int count=0;
    int PWM_RATIO=1;
    int PWM_COUNT_MAX=max;
    int UP=1;
    mPORTBSetPinsDigitalOut(BIT_7);
    while (1)
    {
        while(count<PWM_RATIO)
        {
            count++;
        }
        mPORTBToggleBits(BIT_7);
        while(count<PWM_COUNT_MAX)
        {
            count++;
        }
        mPORTBToggleBits(BIT_7);
        count=0;

        if(UP==1)
            PWM_RATIO++;
        else
            PWM_RATIO--;

        if(PWM_RATIO==PWM_COUNT_MAX)
            UP=0;
        if(PWM_RATIO==0)
            UP=1;
    }
}

void blinkLed(int speed){
    int i=0;

    mPORTBSetPinsDigitalOut(BIT_7);
    while (1)
    {
        for(i=0;i<speed;i++)
            ;
        mPORTBToggleBits(BIT_7);
    }
}
