#include "board_config.h"

#include "bk953x_handler.h"
#include "adc_button_handler.h"
#include "ad22650_handler.h"
#include "flash_handler.h"

#include "ht1621.h"
#include "systick.h"
#include "ft32f0xx.h"

uint8_t Ht1621Tab[] = {0x00, 0x00, 0x00, 0x00};

int main(void)
{
  int err_code = 0;

  trace_init();

  /*greeting*/
  trace_debug("\n\r\n\r");
  trace_debug("       *** Welcome to the Project ***\n\r");
  trace_debug("\n\r");

  trace_debug("LCD Test\r\n");

  SysTick_Init();
  HT1621_Init();
  HT1621_WriteAllData(0, Ht1621Tab, 16); //清除LCD显示数据

  Delay_ms(10);
  Display();

  trace_debug("please input hh：mm：ss to change time\r\n");

  trace_info("Start loop\n\r");
  while (1)
  {
    // app_sched_execute(&m_app_scheduler);
  }
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
