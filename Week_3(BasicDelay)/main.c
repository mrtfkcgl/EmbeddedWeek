
// PIC16F1938 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1

// CONFIG1
#pragma config FOSC = ECH       // Oscillator Selection (ECH, External Clock, High Power Mode (4-32 MHz): device clock supplied to CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable (All VCAP pin functionality is disabled)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ              8000000

uint8_t DelayCounter = 0;
const uint8_t Digit[16]=
{
    0xBF,
    0x86,
    0xBB,
    0xCF,
    0xE6,
    0xed,
    0xfc,
    0x87,
    0xff,
    0xef,
    0xf7,
    0xfc,
    0xb9,
    0xde,
    0xf9,
    0xf1
    
};

void __interrupt() ISR(void)
{
    if(TMR0IF == 1)
    {
       DelayCounter++; // 1ms 
       RB7 =~ RB7;
        
      TMR0 = 247;
      TMR0IF = 0;  
    }
}

void delay_MS(uint8_t a) 
{
    DelayCounter = 0; 
    while(a > DelayCounter); 
}

void InterruptsEnable(void)
{
    GIE = 1;
    PEIE = 1;
}
void TimerZeroInit(void)
{
     
    
    TMR0CS = 0;
    
    
    PSA = 0;
    PS0 = 1;
    PS1 = 1;
    PS1 = 1;
    
    TMR0 = 247;
    TMR0IF =0;
    
    
    
  
    TMR0IE = 1;
}
void main(void) {
    
    

    TRISB = 0x00;
    RB7 = 0;
    TRISA = 0x00;
    
    TimerZeroInit();
    InterruptsEnable();

    
    
    
    while(1)
    {  
        RA0 =1;
       delay_MS(250);
       RA0 = 0;
         delay_MS(250);
    }
    return;
}
