/* 
 * File:   tuner.h
 * Author: kvheyen
 *
 * Created on September 19, 2013, 3:08 PM
 */

#ifndef TUNER_H
#define	TUNER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <plib.h>

/* MACRO DEFENITIONS FOR TUNER SECTION OF FM1216ME */

#define I2C_ADDRESS_TUNER       0x61 // FM1216ME p.12   110 0001

#define TUNER_DB1(freq,ifreq,step) ((int) ( ((freq+ifreq)/step) & 0x7F00 ) >> 8 )

#define TUNER_DB2(freq,ifreq,step) ((int) ( ((freq+ifreq)/step) & 0x00FF ) >> 0 )

#define TUNER_CB(config)            (config|0x80)

    #define TUNER_CB_PLL_POS            0
    #define TUNER_CB_PLL_ON             ((0x0) << TUNER_CB_PLL_POS)
    #define TUNER_CB_PLL_OFF            ((0x1) << TUNER_CB_PLL_POS)

    #define TUNER_CB_STEPSIZE_POS       1
    #define TUNER_CB_STEPSIZE_50KHZ     ((0x0) << TUNER_CB_STEPSIZE_POS)
    #define TUNER_CB_STEPSIZE_31K25HZ   ((0x1) << TUNER_CB_STEPSIZE_POS)
    #define TUNER_CB_STEPSIZE_166K7HZ   ((0x2) << TUNER_CB_STEPSIZE_POS)
    #define TUNER_CB_STEPSIZE_62K5HZ    ((0x3) << TUNER_CB_STEPSIZE_POS)

    #define TUNER_CB_TEST_POS           3
    #define TUNER_CB_TEST_DEFAULT       ((0x1) << TUNER_CB_TEST_POS)

    #define TUNER_CB_CP_POS             7
    #define TUNER_CB_CP_LOW             ((0x0) << TUNER_CB_CP_POS)
    #define TUNER_CB_CP_HIGH            ((0x1) << TUNER_CB_CP_POS)

#define TUNER_BB(config)            (config)

    #define TUNER_BB_L                  (0x01)      // LOW BAND         (48.25 to 160.00MHz)
    #define TUNER_BB_M                  (0x02)      // MID BAND         (160.00 to 442.00 MHz)
    #define TUNER_BB_H                  (0x04)      // HIGH BAND        (442.00 to 863.25 MHz)
    #define TUNER_BB_FMS                (0x19)      // FM BAND STEREO   (87.50 to 108.00MHz)
    #define TUNER_BB_FMM                (0x59)      // FM BAND MONO     (87.50 to 108.00MHz)
    #define TUNER_BB_FM                 (0x08)
    #define TUNER_BB_TV                 (0x10)

#define TUNER_AB(config)            (config)

    #define TUNER_AB_AGC_POS            4
    #define TUNER_AB_AGC_112            ((0x2) << TUNER_AB_AGC_POS)
    #define TUNER_AB_AGC_109            ((0x3) << TUNER_AB_AGC_POS)
    #define TUNER_AB_AGC_106            ((0x4) << TUNER_AB_AGC_POS)
    #define TUNER_AB_AGC_103            ((0x5) << TUNER_AB_AGC_POS)
    #define TUNER_AB_AGC_EXT            ((0x6) << TUNER_AB_AGC_POS)
    #define TUNER_AB_AGC_DIS            ((0x7) << TUNER_AB_AGC_POS)

    #define TUNER_AB_ATC_POS            7
    #define TUNER_AB_ATC_SLOW           ((0x0) << TUNER_AB_ATC_POS)
    #define TUNER_AB_ATC_FAST           ((0x1) << TUNER_AB_ATC_POS)


#define TUNER_IF_FREQ       33300000    // TDA9887 datasheet, Table 17
#define TUNER_LOWBAND_L     48250000    // FM1216ME datasheet, p3
#define TUNER_LOWBAND_U     160000000   // FM1216ME datasheet, p3
#define TUNER_MIDBAND_L     160000000   // FM1216ME datasheet, p3
#define TUNER_MIDBAND_U     442000000   // FM1216ME datasheet, p3
#define TUNER_HIGHBAND_L    442000000   // FM1216ME datasheet, p3
#define TUNER_HIGHBAND_U    863250000   // FM1216ME datasheet, p3

/* MACRO DEFENITIONS FOR IF SECTION OF FM1216ME (TDA9887) */

#define I2C_ADDRESS_IF          0x43 // FM1216ME p.15   100 0011
#define I2C_ADDRESS_IF_SAD_B    0x00 // FM1216ME p.15
#define I2C_ADDRESS_IF_SAD_C    0x01 // FM1216ME p.15
#define I2C_ADDRESS_IF_SAD_E    0x02 // FM1216ME p.15

// TODO: Make macros for progamming the IF section


/* FUNCTION DECLARATIONS */

BOOL writeIF(UINT8 BDATA, UINT8 CDATA, UINT8 EDATA);
UINT8 readIF();
BOOL writeTuner(UINT8 DB1, UINT8 DB2, UINT8 CB, UINT8 BB, UINT8 AB);
UINT8 readTuner();

void initRadio();
void set98MHz();
void setPAL();
void setRadio(unsigned int freq, unsigned int stepsize);

#ifdef	__cplusplus
}
#endif

#endif	/* TUNER_H */

