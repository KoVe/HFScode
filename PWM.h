/* 
 * File:   PWM.h
 * Author: kvheyen
 *
 * Created on September 18, 2013, 10:27 AM
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

void startPWM(unsigned int dutycycle);
void stopPWM();
void setPWM(int dutycycle);
int ADC2PWM(int ADC10bitValue);

#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

