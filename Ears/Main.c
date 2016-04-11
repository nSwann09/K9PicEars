/*
 * File:   Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/INT OSC @16 MHz, 5v
 * Program: 06_EUSART
 * Compiler: XC8 (v 1.35, MPLAX X v3.10)
 * Program Version: 1.0
 * 
 * Program Description: Demonstrates EUSART routines
 *
 * Hardware Description: EMIC 2 TTS Modules is connected as follows:
 *                          GND     -> GND
 *                          5V      -> 5V
 *                          SOUT    -> RC4
 *                          SIN     -> RC3
 * 
 * A PC1602J-L 16x2 LCD is connected to PORTD as per header file. Headphones
 * were used for audio output but can alternatively be sent to amplifier and
 * speaker.
 * 
 * 
 * Dependencies:
 *  16F1717_STD.h
 *  16F1717_STD.c
 *  EUSART.h
 *  EUSART.C
 *  LCD.h
 *
 *
 * Created on January, 21st , 2016, 12:35 AM
 */

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
//Configuration setup
#include "16F1717_STD.h"
#include "pca9685.h"

/*******************************************************************************
 * Function: void initMain()
 *
 * Returns: Nothing
 *
 * Description: Initializations for main
 * 
 * Usage: void initMain()
 ******************************************************************************/
void initMain() {
    // 32MHz clock
    internal_32();

    // initialize the device
    //SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    // Setup I2C
    I2C_Pin_Initialize();
    I2C_Init();
    __delay_ms(1000);
   // SSD1306_Init(0x78);
   // SSD1306_Init(0x7A);
    pca9685_init(PCA9685);
}

/*******************************************************************************
 * Function: void main()
 *
 * Returns: Nothing
 *
 * Description: Program Start
 *
 *******************************************************************************/

void main() {

    // Call setups
    initMain();


    LATC = 0x0;
    ANSELC = 0xCE;
    WPUC = 0xFF;
    TRISC = 0x80;
    int i = 0;
    while (i < 2) {
        LATCbits.LATC0 ^= 1;
        i++;
    }
    LATCbits.LATC0 ^= 0;
    int on = 0;
       
    pca9685_brightness(PCA9685,22,0);
    
    long pwm = 0; 
    // Main loop
    while (1) {
        if (on > 0) {
            on = 0;
            // SSD1306_Clr8(1, 15, on); // Print the text on the line 0, column 0, with inverted colors 
            // SSD1306_Clr8(0, 15, on); // Print the text on the line 0, column 0, with inverted colors        
            
        } else {
            on = 1;
            //SSD1306_Clr8(1, 15, on); // Print the text on the line 0, column 0, with inverted colors  
            //SSD1306_Clr8(0, 15, on); // Print the text on the line 0, column 0, with inverted colors   
            
        }

        //                    SSD1306_Set_Cursor1(0, 0);
        //                    SSD1306_Data(on);
        //                    SSD1306_Set_Cursor1(0, 1);
        //                    SSD1306_Data(on);
        //                    SSD1306_Set_Cursor1(0, 2);
        //                    SSD1306_Data(on);
        //                    SSD1306_Set_Cursor1(0, 3);
        //                    SSD1306_Data(on);
        //                    SSD1306_Set_Cursor1(0, 4);
        //                    SSD1306_Data(on);
        //                    SSD1306_Set_Cursor1(0, 5);
        //                    SSD1306_Data(on);
        //                    SSD1306_Set_Cursor1(0, 6);
        //                    SSD1306_Data(on);
        //                    SSD1306_Set_Cursor1(0, 7);
        //                    SSD1306_Data(on);
        //                    SSD1306_Set_Cursor1(1, 0);
        //                    SSD1306_Data(on);
        //                    SSD1306_Set_Cursor1(1, 1);
        //                    SSD1306_Data(on);
        //                    SSD1306_Set_Cursor1(1, 2);
        //                    SSD1306_Data(on);
        //                    SSD1306_Set_Cursor1(1, 3);
        //                    SSD1306_Data(on);
        //                    SSD1306_Set_Cursor1(1, 4);
        //                    SSD1306_Data(on);
        //                    SSD1306_Set_Cursor1(1, 5);
        //                    SSD1306_Data(on);
        //                    SSD1306_Set_Cursor1(1, 6);
        //                    SSD1306_Data(on);
        //                    SSD1306_Set_Cursor1(1, 7);
        //                    SSD1306_Data(on);



        // SSD1306_Set_Cursor1(0, 0);
        //for (int y = 0; y < 4; y++) {
        //    SSD1306_Set_Cursor1(y, 0);
        //    for (int i = 0; i < 4; i++) {
        //        SSD1306_Data(on);
        //    }
        //}

        //SSD1306_ClrAll(0x7A, on);
        //SSD1306_ClrAll(0x78, on);
//        //SSD1306_Out8(0x7A, 0, 0, "!", on);
//        SSD1306_OutMine(0x7A, 0, 1, 0, on);
//        SSD1306_OutMine(0x7A, 0, 2, 1, on);
//        SSD1306_OutMine(0x7A, 0, 3, 2, on);
//        SSD1306_OutMine(0x7A, 0, 4, 3, on);
//        SSD1306_OutMine(0x7A, 0, 5, 4, on);
//        SSD1306_OutMine(0x7A, 0, 6, 5, on);
//        SSD1306_Fill(0x78, 0, 1, 5, 3, on);
        //SSD1306_TextFill(0x78, 0, 0, 16, 8, on, on == 1 ? 3 : 2);
//                
//        SSD1306_OutMine(0x7A, 0, 6, 5, on);
//            if(on > 0)
//    {
//                PCA9685_Set_High(LED,on);
//            }
//            else
//            {
//                PCA9685_Set_Low(LED,on);
//            }
        LATCbits.LATC0 = on;
         __delay_ms(5); 
        if(pwm < 4095) 
        { 
            pwm+=5; 
        } 
        else 
        { 
            pwm = 0; 
        } 
        pca9685_send(PCA9685,pwm,1);

         __delay_ms(100);
         pca9685_send(PCA9685,4095,1);
         pca9685_send(PCA9685,95,0);
         __delay_ms(100);
         pca9685_send(PCA9685,3095,1);
         pca9685_send(PCA9685,1095,0);
         __delay_ms(100);
         pca9685_send(PCA9685,2095,1);
         pca9685_send(PCA9685,2095,0);
         __delay_ms(100);
         pca9685_send(PCA9685,1095,1);
         pca9685_send(PCA9685,3095,0);
         __delay_ms(100);
         pca9685_send(PCA9685,95,1);   
         pca9685_send(PCA9685,4095,0);        
         __delay_ms(100);
         pca9685_send(PCA9685,pwm,1);
         pca9685_send(PCA9685,pwm,0);
        //        Lcd_Clear();

    }
    return;
}