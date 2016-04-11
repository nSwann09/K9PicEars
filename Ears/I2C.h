

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set SDA aliases
#define SDA_TRIS               TRISC6
#define SDA_LAT                LATC6
#define SDA_PORT               RC6
#define SDA_WPU                WPUC6
#define SDA_ANS                ANSC6
#define SDA_SetHigh()    do { LATC6 = 1; } while(0)
#define SDA_SetLow()   do { LATC6 = 0; } while(0)
#define SDA_Toggle()   do { LATC6 = ~LATC6; } while(0)
#define SDA_GetValue()         RC6
#define SDA_SetDigitalInput()    do { TRISC6 = 1; } while(0)
#define SDA_SetDigitalOutput()   do { TRISC6 = 0; } while(0)

#define SDA_SetPullup()    do { WPUC6 = 1; } while(0)
#define SDA_ResetPullup()   do { WPUC6 = 0; } while(0)
#define SDA_SetAnalogMode()   do { ANSC6 = 1; } while(0)
#define SDA_SetDigitalMode()   do { ANSC6 = 0; } while(0)
// get/set SCL aliases
#define SCL_TRIS               TRISC7
#define SCL_LAT                LATC7
#define SCL_PORT               RC7
#define SCL_WPU                WPUC7
#define SCL_ANS                ANSC7
#define SCL_SetHigh()    do { LATC7 = 1; } while(0)
#define SCL_SetLow()   do { LATC7 = 0; } while(0)
#define SCL_Toggle()   do { LATC7 = ~LATC7; } while(0)
#define SCL_GetValue()         RC7
#define SCL_SetDigitalInput()    do { TRISC7 = 1; } while(0)
#define SCL_SetDigitalOutput()   do { TRISC7 = 0; } while(0)

#define SCL_SetPullup()    do { WPUC7 = 1; } while(0)
#define SCL_ResetPullup()   do { WPUC7 = 0; } while(0)
#define SCL_SetAnalogMode()   do { ANSC7 = 1; } while(0)
#define SCL_SetDigitalMode()   do { ANSC7 = 0; } while(0)

#define INTERRUPT_GlobalInterruptEnable() (INTCONbits.GIE = 1)
#define INTERRUPT_GlobalInterruptDisable() (INTCONbits.GIE = 0)
#define INTERRUPT_PeripheralInterruptEnable() (INTCONbits.PEIE = 1)
#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)

//Global Vars
int I2C_Temp;

//Defines
#define Idle        !(SSPSTATbits.R_nW | (0x1F & SSPCON2))
#define I2C_Start   (SSPCON2bits.SEN)  /* I2C start */
#define I2C_Restart (SSPCON2bits.RSEN)
#define I2C_Stop    (SSPCON2bits.PEN)  /* I2C stop */


//Functions
void I2C_Init(void);
int I2C_Read8(int address, int RegADDR);
void I2C_Write8(int address, int RegADDR, int val);

void I2C_Pin_Initialize(void);
void SendI2C(char addr, char data);
void WaitMSSP(void);

