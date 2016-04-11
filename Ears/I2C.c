#include "16F1717_STD.h"

void I2C_Pin_Initialize(void) {
    LATA = 0x00;
    TRISA = 0xFF;
    ANSELA = 0x00;
    WPUA = 0x00;

    LATB = 0x00;
    TRISB = 0xFF;
    ANSELB = 0x3F;
    WPUB = 0x00;

    LATC = 0xC0;
    TRISC = 0xFF;
    ANSELC = 0x3C;
    WPUC = 0x00;

    //    LATD = 0x00;
    //    TRISD = 0xFF;
    //    ANSELD = 0xFF;
    //    WPUD = 0x00;

    //    LATE = 0x00;
    //    TRISE = 0x0F;
    //    ANSELE = 0x07;
    //    WPUE = 0x00;

    OPTION_REGbits.nWPUEN = 0x01;


    bool state = GIE;
    GIE = 0;
    //    PPSLOCK = 0x55;
    //    PPSLOCK = 0xAA;
    //    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

    //    SSPDATPPSbits.SSPDATPPS = 0x16; // RC6->MSSP:SDA
    //    RC6PPSbits.RC6PPS = 0x11; // RC6->MSSP:SDA
    //    SSPCLKPPSbits.SSPCLKPPS = 0x17; // RC7->MSSP:SCL
    //    RC7PPSbits.RC7PPS = 0x10; // RC7->MSSP:SCL
    //    PPSLOCK = 0x55;
    //    PPSLOCK = 0xAA;
    //    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS

    // R_nW write_noTX; P stopbit_notdetected; S startbit_notdetected; BF RCinprocess_TXcomplete; SMP High Speed; UA dontupdate; CKE disabled; D_nA lastbyte_address; 
    SSP1STAT = 0x00;
    // SSPEN enabled; WCOL no_collision; CKP Idle:Low, Active:High; SSPM FOSC/4_SSPxADD_I2C; SSPOV no_overflow; 
    SSP1CON1 = 0x28;
    // ACKTIM ackseq; SBCDE disabled; BOEN disabled; SCIE disabled; PCIE disabled; DHEN disabled; SDAHT 100ns; AHEN disabled; 
    SSP1CON3 = 0x00;
    // Baud Rate Generator Value: SSPADD 3;   
    SSP1ADD = 0x03;


    // clear the master interrupt flag
    PIR1bits.SSP1IF = 0;
    // enable the master interrupt
    PIE1bits.SSP1IE = 1;

    GIE = state;


}

void I2C_Init(void) {

    SSP1ADD = 0x12; //Clock ~400KHz with 32MHz FOCS
    SSP1CON1 = 0b00001000;
    SSP1CON2 = 0;
    SSP1CON1bits.SSPEN = 1;
}

int I2C_Read8(int address, int RegADDR) {

    uint8_t DATA;

    while (!Idle); /* Don't start unless the MSSP module is idle */

    I2C_Start = 1; /* Set START bit */
    while (I2C_Start); /* Wait until hardware clears the SEN bit */

    SSPBUF = address;
    while (!Idle);

    SSPBUF = RegADDR;
    while (!Idle);

    I2C_Restart = 1;
    while (I2C_Restart);

    SSPBUF = (address | 0x01);
    while (!Idle);

    SSPCON2bits.RCEN = 1; /* Set Receive Enable bit (Master as a receiver) */
    while (!Idle);

    DATA = SSPBUF;

    SSPCON2bits.ACKDT = 1; /* Acknowledge bit, 0 = acknowledge uint8_t received */
    SSPCON2bits.ACKEN = 1; /* Start Acknowledge sequence */
    while (SSPCON2bits.ACKEN); /* Wait for end of acknowledge sequence */
    SSPCON2bits.ACKDT = 0; /* Acknowledge bit, 0 = acknowledge uint8_t received */

    I2C_Stop = 1; /* Set STOP bit */
    while (!Idle); /* Wait while STOP condition established */

    return DATA;
}

void I2C_Write8(int address, int RegADDR, int val) {

    while (!Idle); /* Don't start unless the MSSP module is idle */

    I2C_Start = 1; /* Set START bit */
    while (I2C_Start); /* Wait until hardware clears the SEN bit */

    SSPBUF = address;
    while (!Idle);

    SSPBUF = (RegADDR | 0x80);
    while (!Idle);

    SSPBUF = val;
    while (!Idle);

    I2C_Stop = 1; /* Set STOP bit */
    while (!Idle); /* Wait while STOP condition established */

}

void i2c_start() {
    while (!Idle); /* Don't start unless the MSSP module is idle */

    I2C_Start = 1; /* Set START bit */
    while (I2C_Start); /* Wait until hardware clears the SEN bit */
}

void i2c_write(char data) {
    SSPBUF = data;
    while (!Idle);
}    

void i2c_stop() {
    I2C_Stop = 1; /* Set STOP bit */
    while (!Idle); /* Wait while STOP condition established */
}
