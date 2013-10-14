#include <plib.h>
#include <math.h>
#include "ADC.h"
#include "config.h"

void runADCmanSampManConv(){

    unsigned int config1, config2, config3, configscan, configport;
    int ADCValue0, ADCValue1, ADCValue2, ADCValue3;
    int prod02, prod13, ampl;

    config1 = (ADC_SAMP_ON | ADC_FORMAT_SIGN_INT32 | ADC_AUTO_SAMPLING_OFF | ADC_CLK_MANUAL);
    config2 = (ADC_VREF_AVDD_AVSS | ADC_SAMPLES_PER_INT_1);
    config3 = (ADC_CONV_CLK_Tcy2 | ADC_CONV_CLK_PB);
    configscan = (SKIP_SCAN_ALL);
    configport = (ENABLE_AN3_ANA);

    SetChanADC10( ADC_CH0_POS_SAMPLEA_AN3 | ADC_CH0_NEG_SAMPLEA_NVREF);
    OpenADC10(config1 ,config2 ,config3 ,configport ,configscan );
    EnableADC10();

    OpenTimer3(T3_ON | T3_IDLE_CON | T3_GATE_OFF | T3_PS_1_1 , ADC_PERIOD_TICKS-1);
    OpenOC1(OC_ON | OC_TIMER_MODE16 | OC_TIMER3_SRC | OC_CONTINUE_PULSE , ADC_START_HOLD-1, ADC_START_TRACK-1);
    PPSOutput(1,RPB3,OC1);

    startPWM(0);
    mPORTBSetPinsDigitalIn(BIT_6);

    int i;
    for(i=0;i<100;i++);

    while(1)
    {
        while(!mT3GetIntFlag());
        ConvertADC10();
        mT3ClearIntFlag();
        while(!BusyADC10());
        ADCValue0=ReadADC10(0);
        setPWM(ADC2PWM(ampl));
        if(ampl>0x1FF)
            mPORTBSetBits(BIT_6);
        else
            mPORTBClearBits(BIT_6);

        while(!mT3GetIntFlag());
        ConvertADC10();
        mT3ClearIntFlag();
        while(!BusyADC10());
        ADCValue1=ReadADC10(0);
        prod13 = (ADCValue1-ADCValue3)*(ADCValue1-ADCValue3);

        while(!mT3GetIntFlag());
        ConvertADC10();
        mT3ClearIntFlag();
        while(!BusyADC10());
        ADCValue2=ReadADC10(0);
        prod02 = (ADCValue0-ADCValue2)*(ADCValue0-ADCValue2);

        while(!mT3GetIntFlag());
        ConvertADC10();
        mT3ClearIntFlag();
        while(!BusyADC10());
        ADCValue3=ReadADC10(0);
        ampl = prod13+prod02;
        sqrt(ampl>>1);
    }
}

void runADCautoSampAutoConv(){

    unsigned int config1, config2, config3, configscan, configport;
    int ADCValue0, ADCValue1, ADCValue2, ADCValue3;

    config1 = (ADC_SAMP_ON | ADC_FORMAT_SIGN_INT32 | ADC_AUTO_SAMPLING_ON | ADC_CLK_TMR);
    config2 = (ADC_VREF_AVDD_AVSS | ADC_SAMPLES_PER_INT_4);
    config3 = (ADC_CONV_CLK_Tcy2 | ADC_CONV_CLK_PB);
    configscan = (SKIP_SCAN_ALL);
    configport = (ENABLE_AN3_ANA);

    SetChanADC10( ADC_CH0_POS_SAMPLEA_AN3 | ADC_CH0_NEG_SAMPLEA_NVREF);
    OpenADC10(config1 ,config2 ,config3 ,configport ,configscan );
    EnableADC10();

    OpenTimer3(T3_ON | T3_IDLE_CON | T3_GATE_OFF | T3_PS_1_1 , ADC_PERIOD_TICKS-1);
    OpenOC1(OC_ON | OC_TIMER_MODE16 | OC_TIMER3_SRC | OC_CONTINUE_PULSE , ADC_START_HOLD-1, ADC_START_TRACK-1);
    PPSOutput(1,RPB3,OC1);

    #ifdef AM_DEMOD
        int ampl;
        startPWM(10);
        mPORTBSetPinsDigitalOut(BIT_6);
    #endif
    #ifdef AM_OUTPUT_IQ
        OpenTimer2(T2_ON, PWM_PERIOD_TICKS);
        OpenOC2( OC_ON | OC_TIMER_MODE16 | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0 );
        OpenOC4( OC_ON | OC_TIMER_MODE16 | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0 );
        PPSOutput(2,RPB5,OC2);
        PPSOutput(3,RPB6,OC4);
    #endif

    int i;
    for(i=0;i<100;i++);

    while(1)
    {
        while(!BusyADC10());
        ADCValue0 = ReadADC10(0);
        ADCValue1 = ReadADC10(1);
        ADCValue2 = ReadADC10(2);
        ADCValue3 = ReadADC10(3);
        #ifdef AM_DEMOD
            ampl = (ADCValue1-ADCValue3)*(ADCValue1-ADCValue3) + (ADCValue0-ADCValue2)*(ADCValue0-ADCValue2);
            ampl = sqrt(ampl>>1);
            setPWM(ADC2PWM(ampl));
            if(ampl>0x0FF)
                mPORTBSetBits(BIT_6);
            else
                mPORTBClearBits(BIT_6);
        #endif
        #ifdef AM_OUTPUT_IQ
            SetDCOC2PWM(ADC2PWM((ADCValue0-ADCValue2+0x3FF)>>2));
            SetDCOC4PWM(ADC2PWM((ADCValue1-ADCValue3+0x3FF)>>2));
        #endif
    }
}

void initADC(unsigned int adc_samples_per_int)
{
    unsigned int config1, config2, config3, configscan, configport;

    config1 = (ADC_SAMP_ON | ADC_FORMAT_SIGN_INT32 | ADC_AUTO_SAMPLING_ON | ADC_CLK_TMR);
    config2 = (ADC_VREF_AVDD_AVSS | adc_samples_per_int);
    config3 = (ADC_CONV_CLK_Tcy2 | ADC_CONV_CLK_PB);
    configscan = (SKIP_SCAN_ALL);
    configport = (ENABLE_AN3_ANA);

    SetChanADC10( ADC_CH0_POS_SAMPLEA_AN3 | ADC_CH0_NEG_SAMPLEA_NVREF);
    OpenADC10(config1 ,config2 ,config3 ,configport ,configscan );
    EnableADC10();

    OpenTimer3(T3_ON | T3_IDLE_CON | T3_GATE_OFF | T3_PS_1_1 , ADC_PERIOD_TICKS-1);
    OpenOC1(OC_ON | OC_TIMER_MODE16 | OC_TIMER3_SRC | OC_CONTINUE_PULSE , ADC_START_HOLD-1, ADC_START_TRACK-1);
    PPSOutput(1,RPB3,OC1);
}