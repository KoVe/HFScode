#include <plib.h>
#include "ADC.h"
#include "PWM.h"
#include "config.h"

/* Inital the ADC configrations
 * ADC sampling clock source : Timer 3, set by parameter "timer3Period", ref to 61132B.pdf P617.
 * ADC convert clock source  : Peripheral clock, set by parameter "config3", ref to 61132B.pdf P622.
 * Track and hold (T&H) control signal source: OC1, original from Timer 3, configured by parameter  "firstComparatorOC1", "secondComparatorOC1", ref to 61132B.pdf P 517.
 */
void initADC(){
    int timer3Period = 400;         // config the timmer 3 frequency
    int firstComparatorOC1 = 200;   // config the first comparator in OC1
    int secondComparatorOC1 = 400;  // config the second comparator in OC2

    //Close ADC before ADC configuration
    CloseADC10();

    //choose timer 3 as the convention clock source for ADC, in this example, the convention clock is set as 100KHz
    OpenTimer3(T3_ON | T3_IDLE_CON | T3_GATE_OFF | T3_PS_1_1 | T3_SOURCE_INT , timer3Period);

    /* In this application, subharmonic sampling technique is implemented, a track and hold circut is designed before the input of ADC.
     * A control signal generated from OC1 (Pin 11) control the track and hold operation, more information see "track and hold" related documentation.*/
    // Output comparator 1 supply the control clock for the switch, the two parameters coudl change the duty cycle of the output square wave
    OpenOC1(OC_ON | OC_TIMER_MODE16 | OC_TIMER3_SRC | OC_CONTINUE_PULSE , firstComparatorOC1, secondComparatorOC1);
    PPSOutput(1,RPB4,OC1);

    /* set Pin AN10 (Pin 25) as the ADC input, and MUXA is implemented*/
    SetChanADC10( ADC_CH0_POS_SAMPLEA_AN10 | ADC_CH0_NEG_SAMPLEA_NVREF);


    /*config1: Used to set AD1CON1              */
    /* hold amplifiers are sampling | A/D Operate in Idle mode | A/D data format 32-bit integer| Conversion trigger from timer3 | Auto sampling Select*/
     unsigned int config1 = (ADC_SAMP_ON | ADC_IDLE_CONTINUE | ADC_FORMAT_INTG32 | ADC_CLK_TMR | ADC_AUTO_SAMPLING_ON);

    /* config2: Used to set AD1CON2             */
     /* Vref+ is AVdd and Vref- is AVss | Offset calibration disable |  Do notScan Input Selections | Interrupt After 1 samples | 1 16-word buffer | use MUXA only*/
     unsigned int config2 = (ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_OFF | ADC_SAMPLES_PER_INT_1 | ADC_ALT_BUF_OFF | ADC_ALT_INPUT_OFF);

    /* config3: Used to set AD1CON3
     * A/D Conversion Clock Source Clock derived from PB clock
     * Set sample time*/
     /* Conversion Clock from PB clock | ADCS = 9 | SAMC =8*/
    unsigned int config3 = (ADC_CONV_CLK_PB | ADC_CONV_CLK_5Tcy | ADC_SAMPLE_TIME_8);

    /* configport: configure ports connected to the input of MUX A (and MUX B) as analog inputs
     * Set analog inputs (AN10, pin 25)*/
    /*Enable AN10 in analog mode*/
    unsigned int configport = (ENABLE_AN10_ANA);

    // Do not assign channels to scan (does not matter because ADC_SCAN_OFF is set in config2)
    unsigned int configscan = (SKIP_SCAN_ALL);

    /*Open ADC with above configurations*/
    OpenADC10(config1 ,config2 , config3, configport, configscan);
    ConfigIntADC10(ADC_INT_PRI_5 | ADC_INT_SUB_PRI_0 | ADC_INT_ON);
    EnableADC10();
}

/* ** Interrupt function of ADC interrupt
 * Introduction: ....
 *
 * Preconditions : INTEnableSystemMultiVectoredInt() is needed to enable ADC interrupt
 */
void __ISR(_ADC_VECTOR, IPL5) AdcHandler(void) {
    unsigned int ADCSamp = ReadADC10(0);
    mAD1ClearIntFlag();
    mPORTBToggleBits(BIT_5); /* Toggle bit to measure the sampling frequency (half) */ 
    setPWM(ADC2PWM(ADCSamp));
//    if (ADCSamp>0x1FF)
//        setPWM(ADC2PWM(ADCSamp));
//    else
//        setPWM(ADC2PWM(0x3FF-ADCSamp));
}