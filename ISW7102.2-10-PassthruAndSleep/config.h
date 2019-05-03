/* 
 * File:   config.h
 * Author: Scott
 *
 * Created on November 16, 2018, 12:52 PM
 */

#ifndef CONFIG_H
#define	CONFIG_H

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = SWDTEN    // Watchdog Timer Enable (WDT controlled by the SWDTEN bit in the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = ON          // Flash Program Memory Code Protection (Program memory code protection is enabled)
#pragma config CPD = ON         // Data Memory Code Protection (Data memory code protection is enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#define _XTAL_FREQ      8000000

#define MEM_HOLD        LATAbits.LATA0
#define BOOT_CTRL       LATAbits.LATA2
#define nCS_MEM         LATCbits.LATC3
#define SCK_MEM_TRIS    TRISCbits.TRISC0
#define SDI_MEM_TRIS    TRISCbits.TRISC1
#define SDO_MEM_TRIS    TRISCbits.TRISC2
#define nCS_MEM_TRIS    TRISCbits.TRISC3
#define ATBUS_TX_TRIS   TRISCbits.TRISC4
#define ATBUS_IM_TRIS   TRISCbits.TRISC5
#define BOOT_SEL        LATAbits.LATA4
#define nMD_PWR         LATAbits.LATA5
//#define              LATAbits.LATA4
//#define          PORTAbits.RA5
//#define ATBUS_IM_TRIS   TRISCbits.TRISC5
//#define    TRISCbits.TRISC4

//#define LED_ON()        LED=0
//#define LED_OFF()       LED=1
#define MEM_SPI_BEGIN() nCS_MEM=0
#define MEM_SPI_END()   nCS_MEM=1

#define CRC16           0x8005

#define _1MIN           0x100//7A        // for timer 2 with 1:64 prescale & 1:1 postscale



void init_pic();
void check_state();
void ascii_to_mem(uint8_t dataBuf[], uint8_t len);
void ascii_to_hex(uint8_t dataBuf[], uint8_t len);
void intel_to_mem(uint8_t dataBuf[], uint8_t len);
void save_to_mem(uint8_t dataBuf[], uint8_t len);
void blink();
void prepare_for_sleep();

enum OperationalState {
    Passthrough,
    Datasave,
};
enum OperationalState state;

uint8_t modemChar = 0;
uint8_t tempUARTBuf[3] = {0};
uint8_t rawData[60] = {0};
uint8_t memData[30] = {0};
uint8_t rdpos = 0, mdpos = 0;
uint16_t crcResult = 0, currentAddr = 0;

bool checksumOK = false;
bool okToAddChar = false;

#endif	/* CONFIG_H */