/* 
 * File:   I2C.h
 * Author: kvheyen
 *
 * Created on September 19, 2013, 2:54 PM
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <plib.h>

#define I2C_CLOCK_FREQ          1000
#define I2C_BUS                 I2C1

void initI2C();
BOOL writeI2C(UINT8 I2C_ADDRESS, UINT8 *data, int nelems);
UINT8 readI2C(UINT8 I2C_ADDRESS);


#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

