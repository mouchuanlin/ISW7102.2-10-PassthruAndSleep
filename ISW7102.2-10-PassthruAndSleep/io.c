#include "config.h"
#include "io.h"


bool ota_receive_ready(uint8_t temp)
{
    uint8_t copyBuf[sizeof(tempUARTBuf)];
    for (uint8_t j = 0; j < sizeof(tempUARTBuf); j++)
        copyBuf[j] = tempUARTBuf[j];
    for (uint8_t i = 0; i < sizeof(tempUARTBuf) - 1; i++)
        tempUARTBuf[(uint8_t)(i + 1)] = copyBuf[i];             // shift all entries by one
    tempUARTBuf[0] = temp;                          // store last-received byte
    if (tempUARTBuf[0] == 'Q'/*'&'*/ && tempUARTBuf[1] == 'F'/*'&'*/ && tempUARTBuf[2] == 'R'/*'&'*/)  // check for OTA req (in this case, RFQ)
        return true;
    else
        return false;
}


bool header_received(uint8_t temp)
{
    uint8_t copyBuf[sizeof(tempUARTBuf)];
    for (uint8_t j = 0; j < sizeof(tempUARTBuf); j++)
        copyBuf[j] = tempUARTBuf[j];
    for (uint8_t i = 0; i < sizeof(tempUARTBuf) - 1; i++)
        tempUARTBuf[(uint8_t)(i + 1)] = copyBuf[i];             // shift all entries by one
    tempUARTBuf[0] = temp;                          // store last-received byte
    if (tempUARTBuf[0] == 'D'/*'&'*/ && tempUARTBuf[1] == 'E'/*'&'*/ && tempUARTBuf[2] == 'R'/*'&'*/)  // check for header (in this case, RED)
        return true;
    else
        return false;
}



void init_mem()
{
    init_spi();
//    erase_mem();
}


//void start_timer()
//{
//    T1CONbits.nT1SYNC = 1;
//    T1CONbits.TMR1CS = 0b00;//10
//    T1CONbits.T1CKPS = 0b11;
//    PIE1bits.TMR1IE = 1;
//    INTCONbits.PEIE = 1;
//    PIR1bits.TMR1IF = 0;
//    INTCONbits.GIE = 1;
//    T1CONbits.TMR1ON = 1;
//}




//void stop_timer()
//{
//    T1CONbits.TMR1ON = 0;
//    PIE1bits.TMR1IE = 0;
//    PIR1bits.TMR1IF = 0;
//    timedOut = false;
//}