/*
 * SPI.h
 *
 *  Created on: 2016 márc. 14
 *      Author: Szako
 */

#ifndef INCLUDE_SPI_H_
  #define INCLUDE_SPI_H_

  #include "F2806x_Device.h"
  #include "F2806x_GlobalPrototypes.h"
  #include "F2806x_Spi.h"
  #include "gen_types.h"
  #include "inic.h"

  typedef enum {
    SPI_MODE_A,
    SPI_MODE_B,
    SPI_MODE_C,
    SPI_MODE_D
  } SPICLKMode_t;

  typedef enum {
    DATALENGTH_8BIT,
	DATALENGTH_16BIT
  } SPIDataLength_t;

  typedef struct {
    volatile struct SPI_REGS *SPIInst;
    uint32_t Speed;
    SPICLKMode_t Mode;
    SPIDataLength_t DataLength;
  } SPIStruct_t;

  typedef enum {
    HIGH,
    LOW
  } SPICSState_t;

  void SPI_Init_Clocks(void);
  void SPI_Init_GPIOs(void);
  void SPI_Init(SPIStruct_t *SPI);
  void SPI_CS_Assert(SPICSState_t State);
  void SPI_Set_CLKMode(SPIStruct_t *SPI, SPICLKMode_t CLKMode);
  void SPI_Set_DataLength(SPIStruct_t *SPI, SPIDataLength_t DataLength);
  void SPI_Set_Speed(SPIStruct_t *SPI, uint32_t Speed);

  void SPI_Transmit_8bit(SPIStruct_t *SPI, uint8_t Data);
  void SPI_Transmit_16bit(SPIStruct_t *SPI, uint16_t Data);
  void SPI_Transmit_32bit(SPIStruct_t *SPI, uint32_t Data);
  void SPI_Receive_8bit(SPIStruct_t *SPI, uint8_t *Data);
  void SPI_Receive_16bit(SPIStruct_t *SPI, uint16_t *Data);
  void SPI_Receive_32bit(SPIStruct_t *SPI, uint32_t *Data);
  void SPI_TransmitReceive_16bit(SPIStruct_t *SPI, uint16_t DataOut, uint16_t *DataIn);
  #endif /* INCLUDE_SPI_H_ */
