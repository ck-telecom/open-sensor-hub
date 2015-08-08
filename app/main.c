#include "cmsis_os.h"

#include "led-driver.h"

osThreadId id_table[8];


extern osThreadId uart_thread_init(void);
extern void i2c_slave_task_init(void);

void led_thread(void const *arg)
{

	while (1) {
//        LED_On(0);
//        LED_On(1);
//        osDelay(500);
//        LED_Off(0);
//        LED_Off(1);
        osDelay(500);
	}
}
osThreadDef(led_thread, osPriorityNormal, 1, 0);

int main()
{
    LED_Initialize();
//    LED_On(0);
//    LED_On(1);
//    LED_On(2);
//    LED_On(3);
    if (osKernelInitialize() != osOK) {        // check osStatus for other possible valid values
    // exit with an error message
    }
    id_table[2] = osThreadCreate(osThread(led_thread), NULL);
    id_table[0] = uart_thread_init();
  i2c_slave_task_init();
    if (osKernelStart() != osOK)  {             // start the kernel
        LED_Off(LED_YELLOW);                                                // kernel could not be started
    }
//    while (1) {
//        //error indicator
//    }

    return 0;
}
