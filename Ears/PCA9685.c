/*
 * File:   SSD1306.c
 * Author: Nathan.Swann
 *
 * Created on 14 March 2016, 14:48
 */

#define _XTAL_FREQ 8000000
#include <xc.h>
#include <math.h>
#include "I2C.h"

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9


#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD

/* Send a command */
void PCA9685_Set_Mode1(int address, char wData) {
    I2C_Write8(address, PCA9685_MODE1, wData); // Send the address of the display
}

void PCA9685_Set_Prescale(int address, char wData) {
    I2C_Write8(address, PCA9685_PRESCALE, wData); // Send the address of the display
}

//void PCA9685_Init(int address) {
//    float freq = 900;
//    PCA9685_Set_Mode1(address, 0b00000000);
//    freq = freq * 0.9;  // Correct for overshoot in the frequency setting (see issue #11).
//  float prescaleval = 25000000;
//  prescaleval /= 4096;
//  prescaleval /= freq;
//  prescaleval -= 1;
//  float prescale = floor(prescaleval + 0.5);
//  int ps = prescale;
//  int oldmode = 0b00000000;
//  int newmode = (oldmode&0x7F) | 0x10; // sleep
//  PCA9685_Set_Mode1(address, newmode); // go to sleep
//  PCA9685_Set_Prescale(address, prescale); // set the prescaler
//  PCA9685_Set_Mode1(address, oldmode);
//  //__delay_ms(5);
//  //PCA9685_Set_Mode1(address,  oldmode | 0xa1);  //  This sets the MODE1 register to turn on auto increment.
//                                          // This is why the beginTransmission below was not working.
//}

void PCA9685_Init(int address) {
    PCA9685_Set_Mode1(address, 0x00);
    int frequencyHz = 200;
    double preScale = 25000000.0; // 25MHz
            preScale /= 4096; // 12-bit
            preScale /= frequencyHz;

            preScale -= 1.0;

            //log.Trace(m => m("Setting PWM frequency to {0} Hz", frequencyHz));
            //log.Trace(m => m("Estimated pre-maximum: {0}", preScale));

            double prescale = floor(preScale + 0.5);

            //log.Trace(m => m("Final pre-maximum: {0}", prescale));

            int oldmode = 0x00;
            int newmode = ((oldmode & 0x7F) | 0x10); // sleep


           PCA9685_Set_Mode1(address, newmode); // go to sleep

            PCA9685_Set_Prescale(address,floor(prescale));
            PCA9685_Set_Mode1(address, oldmode);

            __delay_ms(5);

            PCA9685_Set_Mode1(address, oldmode | 0x80);
    
    
    }

/* Set the cursor position */
void PCA9685_Set_High(int address, int pin) {
    int on = 0;
    int off = 4095;
    
    if(pin > 0)
    {
        off = 1;
    }
    
    //I2C_Write8(address, ALLLED_ON_L, on);
    I2C_Write8(address, ALLLED_ON_H, 0x10);
    //I2C_Write8(address, ALLLED_OFF_L, off);
    I2C_Write8(address, ALLLED_OFF_H,  0x00);
    
//    I2C_Write8(address, LED0_ON_L+4*pin, on);
//    I2C_Write8(address, LED0_ON_H+4*pin, on>>8);
//    I2C_Write8(address, LED0_OFF_L+4*pin, off);
//    I2C_Write8(address, LED0_OFF_H+4*pin, off>>8);
}

void PCA9685_Set_Low(int address, int pin) {
    int on = 0;
    int off = 1;
    
            I2C_Write8(address, ALLLED_ON_H, 0);
            I2C_Write8(address, ALLLED_OFF_H, 4000);
//    I2C_Write8(address, LED0_ON_L+4*pin, on);
//    I2C_Write8(address, LED0_ON_H+4*pin, on>>8);
//    I2C_Write8(address, LED0_OFF_L+4*pin, off);
//    I2C_Write8(address, LED0_OFF_H+4*pin, off>>8);
}

/* Escreve um texto com caracteres 8x8 na posição especificada */
void PCA9685_Set_Med(int address, int pin) {
    int on = 0;
    int off = 2000;
    
    I2C_Write8(address, LED0_ON_L+4*pin, on);
    I2C_Write8(address, LED0_ON_H+4*pin, on>>8);
    I2C_Write8(address, LED0_OFF_L+4*pin, off);
    I2C_Write8(address, LED0_OFF_H+4*pin, off>>8);
}


        /// <summary>
        /// Sets a single PWM channel
        /// </summary>
        /// <param name="channel">The channel.</param>
        /// <param name="on">The on values.</param>
        /// <param name="off">The off values.</param>
        void PCA9685_Set_Pwm(int address, int on, int off)
        {
            I2C_Write8(address,ALLLED_ON_L, on & 0xFF);
            I2C_Write8(address,ALLLED_ON_H, on >> 8);
            I2C_Write8(address,ALLLED_OFF_L, off & 0xFF);
            I2C_Write8(address,ALLLED_OFF_H, off >> 8);
        }