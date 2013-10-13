#include "demo.h"
#include <plib.h>
#include "buttons.h"
#include "I2C.h"
#include "tuner.h"
#include "config.h"

/**********************************************/
/*              test led                      */
/**********************************************/
/*  Introduction:
 */
void demoButton(){
    startPWM(PWM_PERIOD_TICKS / 2);
    if(initButton()==BIT_10)
        setPWM(PWM_PERIOD_TICKS/4);
    else
        setPWM(3*PWM_PERIOD_TICKS/4);

    INTEnableSystemMultiVectoredInt();

    fadeLed(1500);
}
/**********************************************/
/*              test I2C                      */
/**********************************************/
/*  
 */
void demoI2C(){

        UINT8               dataIF[4],dataTuner[5];
        int i;

        initI2C();

        //FM1216E p.20
        dataIF[0] =   0x00;
        dataIF[1] =   0x0E;
        dataIF[2] =   0xD0;
        dataIF[3] =   0x77;

        dataTuner[0] = 0x08;
        dataTuner[1] = 0x7E;
        dataTuner[2] = 0x80;
        dataTuner[3] = 0x19;
        dataTuner[4] = 0xA0;

        while(1) {
            writeI2C(I2C_ADDRESS_IF,dataIF ,4);
            for(i=0;i<10000;i++);                   // Wait 10000 cycles, makes the waveforms more clear (oscilloscope)
            readI2C(I2C_ADDRESS_IF);
            for(i=0;i<10000;i++);
            writeI2C(I2C_ADDRESS_TUNER,dataIF ,5);
            for(i=0;i<10000;i++);
            readI2C(I2C_ADDRESS_TUNER);
            for(i=0;i<1000000;i++);
        }
}
/**********************************************/
/*              test setTuner                 */
/**********************************************/
/*  Introduction:
 */
void demoTuner(){
    int i;
    initI2C();

    while(1) {
        set98MHz();
        for(i=0;i<1000000;i++);
    }
}

/**********************************************/
/*              test ADC                      */
/**********************************************/
void demoADC(){
    initADC();
    startPWM(200);
    INTEnableSystemMultiVectoredInt();
    while(1);
}