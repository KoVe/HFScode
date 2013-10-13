#include "tuner.h"
#include "I2C.h"

/* These functions provide communication with 2 chips inside the FM1216ME
 * Details on the meaning of the various data bytes can be found in the
 * datasheet.
 */


BOOL writeIF(UINT8 BDATA, UINT8 CDATA, UINT8 EDATA)
{
    UINT8 data[4];

    data[0] = I2C_ADDRESS_IF_SAD;
    data[1] = BDATA;
    data[2] = CDATA;
    data[3] = EDATA;
    
    writeI2C(I2C_ADDRESS_IF, data ,4);

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
void set98MHz()
{
    UINT8   BDATA, CDATA, EDATA;
    UINT8   DB1, DB2, CB, BB, AB;
    UINT8   temp1,temp2;

    BDATA = 0x0E;
    CDATA = 0xD0;
    EDATA = 0x77;

    DB1   = 0x08;
    DB2   = 0x7E;
    CB    = 0x80;
    BB    = 0x19;
    AB    = 0xA0;

    writeIF(BDATA, CDATA, EDATA);
    temp1 = readIF();
    writeTuner(DB1, DB2, CB, BB, AB);
    temp2 = readTuner();
}
