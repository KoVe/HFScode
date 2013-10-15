#include "tuner.h"
#include "I2C.h"

/* These functions provide communication with 2 chips inside the FM1216ME
 * Details on the meaning of the various data bytes can be found in the
 * datasheet.
 */


BOOL writeIF(UINT8 BDATA, UINT8 CDATA, UINT8 EDATA)
{
    UINT8 data[2];

    data[0] = I2C_ADDRESS_IF_SAD_B;
    data[1] = BDATA;
    writeI2C(I2C_ADDRESS_IF, data ,2);

    data[0] = I2C_ADDRESS_IF_SAD_C;
    data[1] = CDATA;
    writeI2C(I2C_ADDRESS_IF, data ,2);

    data[0] = I2C_ADDRESS_IF_SAD_E;
    data[1] = EDATA;
    writeI2C(I2C_ADDRESS_IF, data ,2);

    return TRUE;
}
UINT8 readIF()
{
    return readI2C(I2C_ADDRESS_IF);
}
BOOL writeTuner(UINT8 DB1, UINT8 DB2, UINT8 CB, UINT8 BB, UINT8 AB)
{
    UINT8 data[5];

    data[0] = DB1;
    data[1] = DB2;
    data[2] = CB;
    data[3] = BB;
    data[4] = AB;

    return writeI2C(I2C_ADDRESS_TUNER, data ,5);
}
UINT8 readTuner()
{
    return readI2C(I2C_ADDRESS_TUNER);
}
/* set Radio does not work without initRadio()
 * TODO: find out why, crf p20 of FM1216ME datasheet
 */
void initRadio()
{
    set98MHz();
}
void set98MHz()
{
    UINT8   BDATA, CDATA, EDATA;
    UINT8   DB1, DB2, CB, BB, AB;
    //UINT8   temp1,temp2;

    BDATA = 0x0E;
    CDATA = 0xD0;
    EDATA = 0x77;

    DB1   = 0x08;
    DB2   = 0x7E;
    CB    = 0x80;
    BB    = 0x19;
    AB    = 0xA0;

    writeIF(BDATA, CDATA, EDATA);
    //temp1 = readIF();
    writeTuner(DB1, DB2, CB, BB, AB);
    //temp2 = readTuner();
}
void setPAL()
{
    UINT8   BDATA, CDATA, EDATA;
    UINT8   DB1, DB2, CB, BB, AB;
    //UINT8   temp1,temp2;

    BDATA = 0x16;
    CDATA = 0x70;
    EDATA = 0x49;

    DB1   = 0x1F;
    DB2   = 0xE2;
    CB    = 0x86;
    BB    = 0x44;
    AB    = 0xA0;

    writeIF(BDATA, CDATA, EDATA);
    //temp1 = readIF();
    writeTuner(DB1, DB2, CB, BB, AB);
    //temp2 = readTuner();
}

void setRadio(unsigned int freq, unsigned int stepsize)
{
    UINT8   BDATA, CDATA, EDATA;
    UINT8   DB1, DB2, CB, BB, AB;



    if      (freq<TUNER_LOWBAND_L)
        blinkLed(100000);
    else if (freq<TUNER_LOWBAND_U)
        BB = TUNER_BB(TUNER_BB_L);
    else if (freq<TUNER_MIDBAND_U)
        BB = TUNER_BB(TUNER_BB_M);
    else if (freq<TUNER_HIGHBAND_U)
        BB = TUNER_BB(TUNER_BB_H);
    else
        blinkLed(100000);

    if       (stepsize == 50000)
    {
        CB  = TUNER_CB(TUNER_CB_PLL_ON|TUNER_CB_STEPSIZE_50KHZ|TUNER_CB_TEST_DEFAULT|TUNER_CB_CP_LOW);
        DB1 = TUNER_DB1(freq,TUNER_IF_FREQ,stepsize);
        DB2 = TUNER_DB2(freq,TUNER_IF_FREQ,stepsize);
    }
    else if  (stepsize== 31250)
    {
        CB  = TUNER_CB(TUNER_CB_PLL_ON|TUNER_CB_STEPSIZE_31K25HZ|TUNER_CB_TEST_DEFAULT|TUNER_CB_CP_LOW);
        DB1 = TUNER_DB1(freq,TUNER_IF_FREQ,stepsize);
        DB2 = TUNER_DB2(freq,TUNER_IF_FREQ,stepsize);
    }
    else if  (stepsize==166700)
    {
        CB  = TUNER_CB(TUNER_CB_PLL_ON|TUNER_CB_STEPSIZE_166K7HZ|TUNER_CB_TEST_DEFAULT|TUNER_CB_CP_LOW);
        DB1 = TUNER_DB1(freq,TUNER_IF_FREQ,stepsize);
        DB2 = TUNER_DB2(freq,TUNER_IF_FREQ,stepsize);
    }
    else if  (stepsize== 62500)
    {
        CB  = TUNER_CB(TUNER_CB_PLL_ON|TUNER_CB_STEPSIZE_62K5HZ|TUNER_CB_TEST_DEFAULT|TUNER_CB_CP_LOW);
        DB1 = TUNER_DB1(freq,TUNER_IF_FREQ,stepsize);
        DB2 = TUNER_DB2(freq,TUNER_IF_FREQ,stepsize);
    }
    else
        blinkLed(100000);

    AB    = TUNER_AB(TUNER_AB_ATC_FAST|TUNER_AB_AGC_109);

    BDATA = 0x08;
    CDATA = 0x10;
    EDATA = 0x08;

    writeIF(BDATA, CDATA, EDATA);
    writeTuner(DB1, DB2, CB, BB, AB);
}