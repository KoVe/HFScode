/* 
 * File:   ADC.h
 * Author: xiaoli
 *
 * Created on September 24, 2013, 1:38 PM
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

#define ADC_PERIOD_TICKS    (100)
#define ADC_START_TRACK     (80)
#define ADC_START_HOLD      (90)

/* Processing performed by runADC*() - values are mutually exclusive */
#define AM_DEMOD      /* Demodulate AM */
//#define AM_OUTPUT_IQ    /* Output the I and Q signal separately */

/*********************************************************************
  Function:         runADCmanSampManConv()
  PreCondition:     None
  Side Effects:     Never returns

  Overview:         Initialize the ADC and process the samples using manual
                    sampling and manual conversion.
    - ADC at AN3 (pin 5)
    - A/D Conversion Clock Source Clock derived from PB clock
    - Conversion trigger source: Clearing sample (SAMP) bit ends sampling and
      starts conversion
    - Autosampling of: sampling begins when sample (SAMP) bit is set
    - Track&Hold control signal source: OC1, linked to timer 3, output at RPB3
      (pin 7)
    - AM-demodulation: analog output (PWM) at RPB5 digital output atRPB6
  Returns:          None
  Note:             None
********************************************************************/
void runADCmanSampManConv();
/*********************************************************************
  Function:         runADCautoSampAutoConv()
  PreCondition:     None
  Side Effects:     Never returns

  Overview:         Initialize the ADC and process the samples using automatic
                    sampling and automatic conversion.
    - ADC at AN3 (pin 5)
    - A/D Conversion Clock Source Clock derived from PB clock
    - Conversion trigger source: Clearing sample (SAMP) bit ends sampling and
      starts conversion
    - Autosampling of: sampling begins when sample (SAMP) bit is set
    - Track&Hold control signal source: OC1, linked to timer 3, output at RPB3
      (pin 7)
    - AM-demodulation: analog output (PWM) at RPB5 digital output atRPB6
  Returns:          None
  Note:             None
********************************************************************/
void runADCautoSampAutoConv();
void initADC();

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

