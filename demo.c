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

        UINT8               dataIF_B[2],dataIF_C[2],dataIF_E[2],dataTuner[5];
        int i;

        initI2C();

        //FM1216E p.20
        dataIF_B[0] =   I2C_ADDRESS_IF_SAD_B;
        dataIF_B[1] =   0x0E;                       // 0000 1110
        dataIF_C[0] =   I2C_ADDRESS_IF_SAD_C;
        dataIF_C[1] =   0xD0;                       // 1101 0000
        dataIF_E[0] =   I2C_ADDRESS_IF_SAD_E;
        dataIF_E[1] =   0x77;                       // 0111 0111

        dataTuner[0] = 0x08;
        dataTuner[1] = 0x7E;
        dataTuner[2] = 0x80;
        dataTuner[3] = 0x19;
        dataTuner[4] = 0xA0;

        while(1) {
            writeI2C(I2C_ADDRESS_IF,dataIF_B ,2);
            for(i=0;i<10000;i++);                   // Wait 10000 cycles, makes the waveforms more clear (oscilloscope)
            writeI2C(I2C_ADDRESS_IF,dataIF_C ,2);
            for(i=0;i<10000;i++);
            writeI2C(I2C_ADDRESS_IF,dataIF_E ,2);
            for(i=0;i<10000;i++);
            readI2C(I2C_ADDRESS_IF);
            for(i=0;i<10000;i++);
            writeI2C(I2C_ADDRESS_TUNER,dataTuner ,5);
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