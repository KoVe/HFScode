#include <plib.h>
#include "config.h"
#include "PWM.h"

/******************************************************************************
 *  void startPWM(unsigned int dutycycle)
 ******************************************************************************
/*  Initialize the PWM: output compare 2, RPB5 (pin14), timer 2
 *
 * The unsigned int dutyclycle proportional to the duty cycle of the PWM signal
 * dutycycle = 0                    -> 0%
 * dutycycle = PWM_PERIOD_TICKS     -> 100%
 *
 * It is advised not to set the dutycycle directly but to use a prescale
 * function (e.g. ADC2PWM(...)) to make the conversion. This way no errors can
 * occur when changing configuration bits or PWM_FREQ
 ******************************************************************************/
void startPWM(unsigned int dutycycle)
{
    /* Map OC2 to RPB5
     * PIC32M1XX/2XX Family Data Sheet, p146, table 11-2
     * 4 Groups of 8 possible output pin selections
     * OC2=>RPB5 is in group 2 */
    PPSOutput(2,RPB5,OC2);
    OpenTimer2(T2_ON, PWM_PERIOD_TICKS-1);
    OpenOC2( OC_ON | OC_TIMER_MODE16 | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, dutycycle, dutycycle );
}

void stopPWM()
{
    CloseOC2();
    CloseTimer2();
}

void setPWM(int dutycycle)
{
    if(dutycycle>ReadPeriod2())
        SetDCOC2PWM(ReadPeriod2());
    else
        SetDCOC2PWM(dutycycle);
}
/******************************************************************************
 *  unsigned int ADC2PWM(unsigned int ADC10bitValue)
 ******************************************************************************
/* Scale a value read by the ADC, so that is lies between 0 and
 * PWM_PERIOD_TICKS
 ******************************************************************************/
int ADC2PWM(int ADC10bitValue)
{
    return (ADC10bitValue*PWM_PERIOD_TICKS) / (2 << (10-1));
}
