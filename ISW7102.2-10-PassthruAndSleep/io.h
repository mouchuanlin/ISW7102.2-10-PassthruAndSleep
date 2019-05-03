/* 
 * File:   io.h
 * Author: Scott
 *
 * Created on November 16, 2018, 3:39 PM
 */

#ifndef IO_H
#define	IO_H

#include <stdint.h>
#include <stdbool.h>


/* CHECK OTA COMMAND FROM SERVER */
bool ota_receive_ready(uint8_t temp);
/* CHECK HEADER RECEIVED FROM SERVER */
bool header_received(uint8_t temp); 
/* UART */
void add_to_crc(uint8_t val);
uint16_t _CRC_16( uint16_t crcVal, uint8_t data);
void init_uart();
void write_uart(unsigned char data);
void receive_data(uint8_t temp);
void init_mem();
void start_timer();
void stop_timer();
/* SPI */
uint8_t send_spi(uint8_t data);
void init_spi();


bool receivedHeader = false, dataReady = false;
bool timedOut = false;

#endif	/* IO_H */