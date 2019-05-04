
#include "config.h"
#include "io.h"


void init_uart()
{
    ATBUS_TX_TRIS = 0;
    ATBUS_IM_TRIS = 1;
    APFCON0bits.RXDTSEL = 0;        // Rx on RC5
    APFCON0bits.TXCKSEL = 0;        // Tx on RC4
    TXSTA = 0x26;       //00100110
    RCSTA = 0x90;       //10010000
    BAUDCON = 0xc8;     //11001000
    //SPBRG = 103;       //19200bps
    SPBRGH = 0;
    BAUDCONbits.WUE = 1;
    SPBRG = 16;         // NOTE: ensure the hub code is always operating at 115.2kbaud uart to the modem, for now.
//    SPBRGH = 0;   

//    RXD_IN = 1;         /* Set RX pin as input */
//    TXD_IN = 0;         /* Set TX pin as output */
//    
//    SYNC = 0;           /* Config uart as asynchronous */
//    SPEN = 1;           /* Enable UART module */
//    
//    /* Enable both Rx and Tx ports */
//    CREN = 1;
//    TXEN = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.RCIE = 1;
    INTCONbits.GIE = 1;
}


void write_uart(unsigned char data)
{
    while (!TRMT);              // Wait for UART TX buffer to empty completely
    TXREG = data;
}


/* 
 * Converts ASCII to hex from modem UART. 
 * Calculates running CRC.
 * Stores hex in 1-1 memory location in external memory chip.
 */
void send_data(uint8_t dataBuf[], uint8_t len)
{
    init_uart();
    for (uint8_t i = 0; i < len; i++)
    {
        write_uart(dataBuf[i]);
    }
}



void add_to_crc(uint8_t val)
{
    crcResult = (uint16_t)(_CRC_16(crcResult, val));
}



/************* CRC16 *******************
*   Calculates the CRC-16 of a single byte the rf protocols.
*   @param  uint16_t crcVal  This iteration of CRC calculations will use this value to start out
*   @param  uint8_t data    This is the data that will generate the resulting CRC
*   @param  uint16_t poly   the polynomial to use for the CRC16
*   @return uint16_t crcVal  The resulting CRC
**************************************************/
uint16_t _CRC_16( uint16_t crcVal, uint8_t data){
    bool carryBit = false;
    for( uint8_t bitMask = 0x80; bitMask != 0; bitMask >>= 1 )
    {
        carryBit = (bool)((crcVal & 0x8000) != 0);// !! is a convenient way to convert a value to a logical true of false value in C only
        crcVal <<= 1;
        if( ( bitMask & data ) != 0 )               //bit is a 1
        {
            if( !carryBit )
                crcVal ^= CRC16;
        }
        else                                      //bit is a 0
        {
            if( carryBit )
                crcVal ^= CRC16;
        }
    }
    return crcVal;
}




bool crc_ok()
{
    return true;
}