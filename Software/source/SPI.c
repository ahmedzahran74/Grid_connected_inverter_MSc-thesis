/*
 * SPI.c
 *
 *  Created on: 2016 márc. 14
 *      Author: Szako
 */

#include "SPI.h"


void SPI_Init_Clocks(void)
{
  SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 0;   // SPI-A
  SysCtrlRegs.PCLKCR0.bit.SPIBENCLK = 1;   // SPI-B
}

void SPI_Init_GPIOs(void)
{
  //--------------------------------------------------------------------------------------
  //  GPIO-12 - PIN FUNCTION = --SPISIMOB--
  GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 3;    // 0=GPIO, 1=#TZ1, 2=SCITXDA, 3=SPISIMOB
  //GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO12 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO12 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-13 - PIN FUNCTION = --SPISOMIB--
  GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 3;    // 0=GPIO, 1=#TZ2, 2=Reserved, 3=SPISOMIB
  //GpioCtrlRegs.GPADIR.bit.GPIO13 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO13 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO13 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-14 - PIN FUNCTION = --SPICLKB--
  GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 3;    // 0=GPIO, 1=#TZ3, 2=SCITXDB, 3=SPICLKB
  //GpioCtrlRegs.GPADIR.bit.GPIO14 = 1;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO14 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO14 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-15 - PIN FUNCTION = --#SPISTEB--
  GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;    // 0=GPIO, 1=ECAP2, 2=SCIRXDB, 3=#SPISTEB
  GpioCtrlRegs.GPADIR.bit.GPIO15 = 1;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO15 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO15 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
}

void SPI_Init(SPIStruct_t *SPI)
{
  SPI_Init_Clocks();

  SPI->SPIInst->SPICCR.bit.SPISWRESET = 0;      // 7      SPI SW Reset
  SPI->SPIInst->SPICCR.bit.CLKPOLARITY = 1;     // 6      Clock polarity=Falling edge
  SPI->SPIInst->SPICCR.bit.SPILBK = 0;          // 4      Loop-back disable
  SPI->SPIInst->SPICCR.bit.SPICHAR = 15;        // 3:0    Character length control = 16
  SPI->SPIInst->SPICTL.bit.OVERRUNINTENA = 0;   // 4      Overrun interrupt disable
  SPI->SPIInst->SPICTL.bit.CLK_PHASE = 1;       // 3      Clock phase select = 1, Delayed
  SPI->SPIInst->SPICTL.bit.MASTER_SLAVE = 1;    // 2      Network control mode = master
  SPI->SPIInst->SPICTL.bit.TALK = 1;            // 1      Master/Slave transmit enable
  SPI->SPIInst->SPICTL.bit.SPIINTENA = 0;       // 0      Interrupt disable
  SPI->SPIInst->SPIBRR = LSPCLK/3000000-1;      //        Baudrate = 10MHz / (9 + 1) = 3MHz
  SPI->SPIInst->SPICCR.bit.SPISWRESET = 1;      // 7      SPI SW Reset: not active

  SPI->SPIInst->SPIFFTX.bit.SPIRST = 0;         // 15     Reset SPI
  SPI->SPIInst->SPIFFTX.bit.SPIFFENA = 1;       // 14     Enhancement enable
  SPI->SPIInst->SPIFFTX.bit.TXFIFO = 0;         // 13     FIFO reset

  SPI->SPIInst->SPIFFRX.bit.RXFFOVFCLR = 1;     // 14     Clear overflow
  SPI->SPIInst->SPIFFRX.bit.RXFIFORESET = 0;    // 13     FIFO reset

  SPI->SPIInst->SPIFFTX.bit.SPIRST = 1;         // 15     enable SPI
  SPI->SPIInst->SPIFFTX.bit.TXFIFO = 1;         // 13     FIFO normal op

  SPI->SPIInst->SPIFFRX.bit.RXFIFORESET = 1;    // 13     FIFO normal op

  SPI->SPIInst->SPIFFCT.bit.TXDLY = 2;          // 7:0    FIFO transmit delay, 2401A ennyit kesleltet

  SPI_Init_GPIOs();
}

void SPI_CS_Assert(SPICSState_t State)
{
  switch(State)
  {
    case HIGH:
      GpioDataRegs.GPASET.bit.GPIO15 = 1;
      break;
    case LOW:
      GpioDataRegs.GPACLEAR.bit.GPIO15 = 1;
      break;
    default:
      GpioDataRegs.GPASET.bit.GPIO15 = 1;
      break;
  }
}

void SPI_Set_CLKMode(SPIStruct_t *SPI, SPICLKMode_t CLKMode)
{

  SPI->Mode = CLKMode;

  switch (SPI->Mode)
  {
    case SPI_MODE_A:
      SPI->SPIInst->SPICCR.bit.CLKPOLARITY = 0;
	  SPI->SPIInst->SPICTL.bit.CLK_PHASE = 0;
      break;
    case SPI_MODE_B:
      SPI->SPIInst->SPICCR.bit.CLKPOLARITY = 0;
  	  SPI->SPIInst->SPICTL.bit.CLK_PHASE = 1;
      break;
    case SPI_MODE_C:
      SPI->SPIInst->SPICCR.bit.CLKPOLARITY = 1;
  	  SPI->SPIInst->SPICTL.bit.CLK_PHASE = 0;
      break;
    case SPI_MODE_D:
      SPI->SPIInst->SPICCR.bit.CLKPOLARITY = 1;
  	  SPI->SPIInst->SPICTL.bit.CLK_PHASE = 1;
      break;
    default:
      SPI->SPIInst->SPICCR.bit.CLKPOLARITY = 0;
  	  SPI->SPIInst->SPICTL.bit.CLK_PHASE = 0;
      break;
  }
}

void SPI_Set_DataLength(SPIStruct_t *SPI, SPIDataLength_t DataLength)
{

  SPI->DataLength = DataLength;

  switch (SPI->DataLength)
  {
    case DATALENGTH_8BIT:
      SpiaRegs.SPICCR.bit.SPICHAR = 7;        //Character length control = 8
      break;
    case DATALENGTH_16BIT:
      SpiaRegs.SPICCR.bit.SPICHAR = 15;        //Character length control = 16
      break;
    default:
      SpiaRegs.SPICCR.bit.SPICHAR = 15;        //Character length control = 16
      break;
  }
}

void SPI_Set_Speed(SPIStruct_t *SPI, uint32_t Speed)
{
  SPI->Speed = Speed;
  SpiaRegs.SPIBRR = LSPCLK/SPI->Speed-1;
}

void SPI_Transmit_8bit(SPIStruct_t *SPI, uint8_t Data)
{
  SPI_Set_DataLength(SPI, DATALENGTH_8BIT);

  SPI->SPIInst->SPITXBUF = Data;
  while (SPI->SPIInst->SPIFFTX.bit.TXFFST != 0);
}

void SPI_Transmit_16bit(SPIStruct_t *SPI, uint16_t Data)
{
  SPI_Set_DataLength(SPI, DATALENGTH_16BIT);

  SPI->SPIInst->SPITXBUF = Data;
  while (SPI->SPIInst->SPIFFTX.bit.TXFFST != 0);
}

void SPI_Transmit_32bit(SPIStruct_t *SPI, uint32_t Data)
{
  SPI_Set_DataLength(SPI, DATALENGTH_16BIT);

  SPI->SPIInst->SPITXBUF = Data >> 16;
  SPI->SPIInst->SPITXBUF = Data & 0xFFFF;
  while (SPI->SPIInst->SPIFFTX.bit.TXFFST != 0);
}

void SPI_Receive_8bit(SPIStruct_t *SPI, uint8_t *Data)
{
  uint8_t Dummy = 0xFF;

  //SPI_Set_DataLength(SPI, DATALENGTH_8BIT);

  SPI->SPIInst->SPITXBUF = Dummy;
  while (SPI->SPIInst->SPIFFTX.bit.TXFFST != 0);

  *Data = SPI->SPIInst->SPIRXBUF;
}

void SPI_Receive_16bit(SPIStruct_t *SPI, uint16_t *Data)
{
  //uint16_t Dummy = 0xFFFF;

  //SPI_Set_DataLength(SPI, DATALENGTH_16BIT);

  //SPI->SPIInst->SPITXBUF = Dummy;
  //while (SPI->SPIInst->SPIFFTX.bit.TXFFST != 0);

  *Data = SPI->SPIInst->SPIRXBUF;
}

void SPI_Receive_32bit(SPIStruct_t *SPI, uint32_t *Data)
{
  uint16_t Dummy = 0xFFFF;

  SPI_Set_DataLength(SPI, DATALENGTH_16BIT);

  SPI->SPIInst->SPITXBUF = Dummy;
  SPI->SPIInst->SPITXBUF = Dummy;
  while (SPI->SPIInst->SPIFFTX.bit.TXFFST != 0);

  *Data = (uint32_t)SPI->SPIInst->SPIRXBUF << 16 + SPI->SPIInst->SPIRXBUF << 16;
}

void SPI_TransmitReceive_16bit(SPIStruct_t *SPI, uint16_t DataOut, uint16_t *DataIn)
{

  SPI_Set_DataLength(SPI, DATALENGTH_16BIT);

  SPI->SPIInst->SPITXBUF = DataOut;
  while (SPI->SPIInst->SPIFFRX.bit.RXFFST == 0);

  *DataIn = SPI->SPIInst->SPIRXBUF;

}
