
#include "config.h"
#include "io.h"


//void ascii_to_mem(uint8_t dataBuf[], uint8_t len)
//{
//    ascii_to_hex(dataBuf, len);       // 1,3,5... array positions filled
//    intel_to_mem(dataBuf, len);   // => memData[]
//    if (checksumOK)
//    {
//        checksumOK = false;
//        save_to_mem(memData, mdpos);
//    }
//}
//
//
//void ascii_to_hex(uint8_t dataBuf[], uint8_t len)
//{
//    uint8_t temp = 0;
//    for (uint8_t i = 0; i < len; i++)
//    {
//        if (dataBuf[i] >= 0x30 && dataBuf <= 0x39)
//            dataBuf[i] -= 0x30;
//        else if (dataBuf[i] >= 0x41 && dataBuf <= 0x46)
//            dataBuf[i] -= 0x41 + 0x0A;
//    }
//    for (uint8_t j = 1; j < len; j++)
//    {
//        temp = (uint8_t)(dataBuf[j - 1] << 4 | dataBuf[j]);
//        dataBuf[j] = temp;
//    }
//}
//
//
//void intel_to_mem(uint8_t dataBuf[], uint8_t len)
//{
//    uint8_t numBytes = dataBuf[1];
//    // 7 = data offset; 2 = checksum offset from end of data
//    uint8_t checksum = dataBuf[numBytes*2 + 7 + 2];
//    
//    currentAddr = (uint16_t)(dataBuf[3] << 8 | dataBuf[5]);
//    
//    for (uint8_t i = 0; i < numBytes; i++)
//    {
//        if (i % 2 == 0)
//            memData[i] = dataBuf[2*i + 11];
//        else
//            memData[i] = dataBuf[2*i + 7];
//        checksum += memData[i];
//    }
//    checksumOK = true;
//}


void save_to_mem(uint8_t dataBuf[], uint8_t len)
{
    MEM_SPI_BEGIN();
    send_spi(currentAddr);
    for(uint8_t i = 0; i < len; i++)
    {
        send_spi(dataBuf[i]);
    }
    MEM_SPI_END();
}