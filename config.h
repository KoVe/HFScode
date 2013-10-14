/* 
 * File:   config.h
 * Author: kvheyen
 *
 * Created on September 18, 2013, 2:01 PM
 *
 * Defenition of some macros
 */

#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

#define XTAL_FREQ           (10000000L)                     // 10MHz Crystal
#define SYS_FREQ            (XTAL_FREQ/2*16/2)              // System Clock Frequency

#define PB_DIV              (1 << DEVCFG1bits.FPBDIV)       // Peripheral Clock Divisor
#define PB_FREQ             (SYS_FREQ/PB_DIV)               // Peripheral Clock Frequency

//#define PWM_FREQ            (50000L)                        // 50kHz PWM frequency
//#define PWM_FREQ            (500000L)                       // 500kHz PWM frequency
#define PWM_FREQ            (1600000L)                      // 1.6MHz PWM frequency
#define PWM_PERIOD_TICKS    (SYS_FREQ/(PB_DIV*PWM_FREQ))


#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

