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

#define I2C_ADDRESS_TUNER       0x61 // FM1216ME p.12
#define I2C_ADDRESS_IF          0x43 // FM1216ME p.15
#define I2C_ADDRESS_IF_SAD      0x00 // FM1216ME p.15

BOOL writeIF(UINT8 BDATA, UINT8 CDATA, UINT8 EDATA);
UINT8 readIF();
BOOL writeTuner(UINT8 DB1, UINT8 DB2, UINT8 CB, UINT8 BB, UINT8 AB);
UINT8 readTuner();
void set98MHz();


#ifdef	__cplusplus
}
#endif

#endif	/* TUNER_H */

