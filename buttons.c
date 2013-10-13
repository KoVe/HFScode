#include <plib.h>
#include "config.h"
#include "buttons.h"
#include "PWM.h"

/* Enable the use of a switch attached to RPB10 (pin 21)
 * Switch is configured so that the voltage at pin 21 is VSS or VDD
 * So no (internal/external) pull-up resistors are required!
 * 
 * When the position of the switch is changed an interupt flag is set 
 * (_CHANGE_NOTICE_VECTOR) and the Interupt Service Routine (ISR) 
 * ChangeNotice_Handler is executed.
 */



unsigned int initButton()
{
    unsigned int initVal;
    mPORTBSetPinsDigitalIn(BIT_10);
    mCNBOpen(CNB_ON|CNB_IDLE_CON,CNB10_ENABLE,CNB_PULLUP_DISABLE_ALL);
    initVal = mPORTBReadBits(BIT_10);
    ConfigIntCNB(CHANGE_INT_PRI_2|CHANGE_INT_ON);
    return initVal;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL2) ChangeNotice_Handler(void)
{
    /* Do something */
    if(mPORTBReadBits(BIT_10)==BIT_10)
        setPWM(PWM_PERIOD_TICKS/4);
    else
        setPWM(3*PWM_PERIOD_TICKS/4);

    /* Clear Flag */
    mCNBClearIntFlag();
}
