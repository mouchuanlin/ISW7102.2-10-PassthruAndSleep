/* 
 * File:   main.c
 * Author: Scott
 *
 * Created on November 16, 2018, 12:52 PM
 */

#include "config.h"
#include "io.h"

/*
 * 
 */
bool minTimerOn = false;
uint16_t _1minTimerCnt = 0;

void __interrupt isr()
{
    if (PIR1bits.RCIF)
    {
        PIR1bits.RCIF = 0;
        modemChar = RCREG;
        okToAddChar = true;
    }
    if (PIR1bits.TMR2IF)
    {
        PIR1bits.TMR2IF = 0;
        _1minTimerCnt++;
        if (_1minTimerCnt >= _1MIN)
        {
            stop_timer();
        }
    }
}

void main()
{
    init_pic();     // enable WDT
    init_uart();    // enable UART
    
    init_mem();
        MEM_SPI_BEGIN();
        send_spi(0xB9);     // Deep PWDN
        MEM_SPI_END();
    while(1)
    {
        check_state();
        if (!minTimerOn)
        {
            prepare_for_sleep();
                CLRWDT();
                SLEEP();
                NOP();
        }
//        __delay_ms(10);
        CLRWDT();
    }
}


void init_pic()
{
    OSCCON = 0b01110000;        // 8MHz INTOSC select
    OPTION_REG = 0b01000111;    // WPU enabled, 1:256 Timer0 prescaler,
                                // interrupt on rising edge of INT pin
    
    ANSELA = 0x00;
    ANSELC = 0x00;
    TRISA = 0b00001000;
    WPUA = 0b00000001;          // MEM_HOLD has WPU enabled
    TRISC = 0b00010000;
    
    PORTA = 0b00111000;
    PORTC = 0b00100000;
    
//    TRISA = 0b00101000;         // MEM_HOLD is high-impedance for now
//    TRISC = 0b00000000;         // SDI, Rx are outputs for now
//                                // nCS made High-Z, it has external PU
//    WPUA = 0b00100000;          // MEM_HOLD has WPU on
//    LED_OFF();
//    blink();
    WDTCONbits.WDTPS = 0b00111;
    WDTCONbits.SWDTEN = 1;
}

void check_state()
{
    switch (state)
    {
        case Passthrough:
            if (okToAddChar)
            {
                okToAddChar = false;
//                if (ota_receive_ready(modemChar))
//                {
////                    state = WaitReady;
//                    BOOT_SEL = 0;
//                    nMD_PWR = 0;
//                    BOOT_CTRL = 0;
//                    start_timer();      // how long to wait?
//                }
//                else
                    write_uart(modemChar);
                    minTimerOn = true;
                    start_timer();
            }
            break;
//        case WaitReady:
//            if (header_received(modemChar) && !timedOut)
//            {
//                timedOut = false;
//                init_mem();
//                state = Datasave;
//                start_timer();      // how long to wait?
//            }
//            else if (timedOut)
//            {
//                reset_ota();
//            }
//            else
//            {
//                if (okToAddChar)
//                {
//                    okToAddChar = false;
//                    write_uart(modemChar);
//                }
//            }
//            break;
//        case Datasave:
//            if (okToAddChar)
//            {
//                okToAddChar = false;
//                if (modemChar == ':')
//                {
//                    rdpos = 0;
//                }
//                else if (modemChar == '\r' || modemChar == '\n')
//                    parse_data();
//                else
//                    rawData[rdpos++] = modemChar
//            }
//            if (reachedEndOfFile)
//            {
//                if (crcOK())
//                {
//                    
//                }
//            }
    }
}


//void blink()
//{
//    LED_ON();
//    __delay_ms(100);
//    CLRWDT();
//    __delay_ms(100);
//    CLRWDT();
//    LED_OFF();
//}


void reset_ota()
{
    stop_timer();
    state = Passthrough;
}




void prepare_for_sleep()
{
    BAUDCONbits.WUE = 1;
    PIE1bits.RCIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}



void start_timer()          // 
{
    _1minTimerCnt = 0;
    
    T2CONbits.T2CKPS = 0b11;        // 1:64 prescale
    T2CONbits.T2OUTPS = 0b00;       // 1:1 postscale
    T2CONbits.TMR2ON = 1;
    PIE1bits.TMR2IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}


void stop_timer()
{
    _1minTimerCnt = 0;
    minTimerOn = false;
    T2CONbits.TMR2ON = 0;
    PIE1bits.TMR2IE = 0;
}