#include "I2C.h"
#include "config.h"
#include <plib.h>


/* initialize I2C configuration
 */
void initI2C(){
    I2CSetFrequency(I2C_BUS, PB_FREQ, I2C_CLOCK_FREQ);
    I2CEnable(I2C_BUS, TRUE);
}

/*  write I2C command
 *  input parameter:
 *      I2C_ADDRESS:    I2C slave address
 *      data:           data (8bit) to be sent
 *      nelems:         number of elements in data
 */
BOOL writeI2C(UINT8 I2C_ADDRESS, UINT8 *data, int nelems){
    I2C_STATUS  status;
    int i;
    int n;
    I2C_7_BIT_ADDRESS   slave7BitAddress;

    I2C_FORMAT_7_BIT_ADDRESS(slave7BitAddress, I2C_ADDRESS, I2C_WRITE);

    while(!I2CBusIsIdle(I2C_BUS));              /* Wait until the bus is idle */
    if(I2CStart(I2C_BUS) != I2C_SUCCESS)
        fadeLed(2000);

    do{
        status = I2CGetStatus(I2C_BUS);
    } while ( !(status & I2C_START) );

    while(!I2CTransmitterIsReady(I2C_BUS));

    for(i=0;i<1000;i++);                        /* Wait 1000 cycles */
    I2CSendByte(I2C_BUS, slave7BitAddress.byte);
    while(!I2CTransmissionHasCompleted(I2C_BUS));
    if(!I2CByteWasAcknowledged(I2C_BUS))
        fadeLed(1000);
    for(i=0;i<1000;i++);

    for(n=0;n<nelems;n++){
        I2CSendByte(I2C_BUS, data[n]);
        while(!I2CTransmissionHasCompleted(I2C_BUS));
        if(!I2CByteWasAcknowledged(I2C_BUS))
            fadeLed(1000);
        for(i=0;i<1000;i++);                    /* Wait 1000 cycles */
    }
    I2CStop(I2C_BUS);
    do {
        status = I2CGetStatus(I2C_BUS);
    } while ( !(status & I2C_STOP) );

    return TRUE;
}

/*  read data from I2C bus
 *  Input parameter:
 *      I2C_ADDRESS: I2C slave address
 */
UINT8 readI2C(UINT8 I2C_ADDRESS){
    I2C_7_BIT_ADDRESS   slave7BitAddress;
    I2C_STATUS  status;
    int i;
    UINT8 result;

    I2C_FORMAT_7_BIT_ADDRESS(slave7BitAddress, I2C_ADDRESS, I2C_READ);
    while(!I2CBusIsIdle(I2C_BUS));                     /* Wait until the bus is idle */
    if(I2CRepeatStart(I2C_BUS) != I2C_SUCCESS)
        fadeLed(1000);
    do{
        status = I2CGetStatus(I2C_BUS);
    } while ( !(status & I2C_START) );

    while(!I2CTransmitterIsReady(I2C_BUS));
    for(i=0;i<1000;i++);
    I2CSendByte(I2C_BUS, slave7BitAddress.byte);
    while(!I2CTransmissionHasCompleted(I2C_BUS));   /* Wait until the transmission has completed */
    if(!I2CByteWasAcknowledged(I2C_BUS))
        fadeLed(1000);
    for(i=0;i<1000;i++);
    if(I2CReceiverEnable(I2C_BUS, TRUE) != I2C_SUCCESS)
        fadeLed(1000);
    for(i=0;i<1000;i++);
    result = I2CGetByte(I2C_BUS);
    for(i=0;i<2000;i++);
    I2CReceiverEnable(I2C1, FALSE);
    if(I2CReceiverEnable(I2C_BUS, TRUE) != I2C_SUCCESS)
        fadeLed(1000);
    for(i=0;i<2000;i++);
    I2CAcknowledgeByte(I2C_BUS,FALSE);
    for(i=0;i<1000;i++);
    I2CStop(I2C_BUS);
    do {
        status = I2CGetStatus(I2C_BUS);
    } while ( !(status & I2C_STOP) );
    return result;
}
