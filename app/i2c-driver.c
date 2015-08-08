#include "Driver_I2C.h"
#include "cmsis_os.h"

#include "led-driver.h"
//extern ARM_DRIVER_I2C Driver_I2C1;
//static ARM_DRIVER_I2C *master = &Driver_I2C1;
extern ARM_DRIVER_I2C Driver_I2C1;
static ARM_DRIVER_I2C *slave = &Driver_I2C1;

extern osThreadId id_table[8];

#define I2C_SALVE_7BIT_ADDR 0x2C
//void i2c_master_init(void)
//{
//    master->Initialize(NULL);
//    master->PowerControl(ARM_POWER_FULL);
//    master->Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_FAST);
//    master->Control(ARM_I2C_BUS_CLEAR, 0);
//}

void i2c_slave_callback(uint32_t event)
{
    if (event == ARM_I2C_EVENT_TRANSFER_DONE) LED_On(0);
    else if (event == ARM_I2C_EVENT_TRANSFER_INCOMPLETE) LED_On(2);
    else if (event == ARM_I2C_EVENT_SLAVE_TRANSMIT) LED_On(2);
    else if (event == ARM_I2C_EVENT_SLAVE_RECEIVE) LED_On(2);
    else if (event == ARM_I2C_EVENT_GENERAL_CALL) LED_On(3);
    else if(event == ARM_I2C_EVENT_ADDRESS_NACK) LED_On(3);
    else if(event == ARM_I2C_EVENT_ARBITRATION_LOST) LED_On(3);
    else if (event == ARM_I2C_EVENT_BUS_ERROR) LED_On(3);
    else if (event == ARM_I2C_EVENT_BUS_CLEAR) LED_On(3);
    else LED_On(1);
    LED_On(1);
    osSignalSet(id_table[1], 0x01);
}

uint32_t i2c_slave_init(void)
{
  int32_t retval;

  retval = slave->Initialize(i2c_slave_callback);        
  retval |= slave->PowerControl(ARM_POWER_FULL);
  retval |= slave->Control(ARM_I2C_OWN_ADDRESS, I2C_SALVE_7BIT_ADDR<<1);  
  retval |= slave->Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_STANDARD/*ARM_I2C_BUS_SPEED_FAST*/);
//    slave->Control(ARM_I2C_BUS_CLEAR, 0);
  if (retval < 0)
		LED_On(1);

  return retval;
}

void i2c_slave_thread(const void *args)
{
	int32_t retval;
	uint8_t buf[4];
	uint32_t len;
	uint32_t bytes;
	i2c_slave_init();

    //osSignalWait(0x01, osWaitForever);
    len = 2;//LED_Toggle(LED_RED);
  retval = slave->SlaveReceive(buf, len);
  if (retval != ARM_DRIVER_OK) {
  }
    //osSignalWait(0x01, osWaitForever);    
    //while (slave->GetStatus().busy);
    //LED_Toggle(LED_BLUE);
    //if ((buf[0] == 0x20) && (buf[1] = 0x00)) 
    //bytes = slave->GetDataCount();//if (bytes == 4) 
    //slave->SlaveTransmit();
    while (1) {
//LED_Toggle(LED_RED);
        osDelay(100);

    }
}
osThreadDef(i2c_slave_thread, osPriorityNormal, 1, 0);

/*osThreadId thread_id*/void i2c_slave_task_init(void)
{
  id_table[1] = osThreadCreate(osThread(i2c_slave_thread), NULL);
      /* return osThreadCreate(osThread(slave_thread), NULL);*/
}