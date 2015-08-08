#include "Driver_SPI.h"
#include "cmsis_os.h"

//#include "spi-driver.h"
//#include "gyroscope.h"

extern ARM_DRIVER_SPI Driver_SPI1;
ARM_DRIVER_SPI *SPIdrv = &Driver_SPI1;

void spi_callback(uint32_t event)
{
    switch (event)
    {
    case ARM_SPI_EVENT_TRANSFER_COMPLETE:
      /* Success: Wakeup Thread */
      //osSignalSet(tid_mySPI_Thread, 0x01);
      break;
    case ARM_SPI_EVENT_DATA_LOST:
      /*  Occurs in slave mode when data is requested/sent by master
            but send/receive/transfer operation has not been started
            and indicates that data is lost. */
      __breakpoint(0);  /* Error: Call debugger or replace with custom error handling */
      break;
    case ARM_SPI_EVENT_MODE_FAULT:
      /*  Occurs in master mode when Slave Select is deactivated and
          indicates Master Mode Fault. */
      __breakpoint(0);  /* Error: Call debugger or replace with custom error handling */
      break;
    }
}

void spi_init(void)
{
  /* Initialize the SPI driver */
  SPIdrv->Initialize(spi_callback);
  /* Power up the SPI peripheral */
  SPIdrv->PowerControl(ARM_POWER_FULL);
  /* Configure the SPI to Master, 8-bit mode @10000 kBits/sec */
  SPIdrv->Control(ARM_SPI_MODE_MASTER | ARM_SPI_CPOL1_CPHA1 | ARM_SPI_MSB_LSB | ARM_SPI_SS_MASTER_SW | ARM_SPI_DATA_BITS(8), 10000000);

  /* Set CS line */
  SPIdrv->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_INACTIVE);
  /* Clear CS line */
  SPIdrv->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_ACTIVE);
}

//u8 l3g4200d_read(u8 reg, u8 *data)
//{
//  u8 val;

//  drv_info->SlaveSelect(ARM_SPI_SS_ACTIVE);
//  drv_info->TransferByte(SPI_READ | SPI_S | reg);
//  val = drv_info->TransferByte(0);
////    SPI_WriteByte(SPI_SENSOR_BUS, SPI_READ | SPI_S | reg);
////    val = SPI_ReadByte(SPI_SENSOR_BUS);
//  drv_info->SlaveSelect(ARM_SPI_SS_INACTIVE);

//    *data = val;
//    return 0;
//}

//u8 l3g4200d_write(u8 reg, u8 data)
//{
//  drv_info->SlaveSelect(ARM_SPI_SS_ACTIVE);
//  drv_info->TransferByte(SPI_WRITE | SPI_S | reg);
//  drv_info->TransferByte(data);
////    SPI_WriteByte(SPI_SENSOR_BUS, SPI_WRITE | SPI_S | reg);
////    SPI_WriteByte(SPI_SENSOR_BUS, data);
//  drv_info->SlaveSelect(ARM_SPI_SS_INACTIVE);

//    return 0;
//}