#include "board_config.h"

#include "bk953x_handler.h"
#include "adc_button_handler.h"
#include "ad22650_handler.h"
#include "flash_handler.h"

#include "ht1621.h"

#define SCHED_MAX_EVENT_DATA_SIZE   8
#define SCHED_QUEUE_SIZE            20

static app_scheduler_t  m_app_scheduler;


MID_TIMER_DEF(m_test_timer);
uint8_t data[4] = { 0x64,0x23,0x18,0x74 };

static char * mp_button[BUTTON_EVENT_MAX] = 
{
  "BUTTON_R_EVENT_SET_PUSH",
  "BUTTON_R_EVENT_SET_RELEASE",
  "BUTTON_R_EVENT_UP_PUSH",
  "BUTTON_R_EVENT_UP_RELEASE",
  "BUTTON_R_EVENT_DOWN_PUSH",
  "BUTTON_R_EVENT_DOWN_RELEASE",
  "BUTTON_R_EVENT_LONG_SET",

  "BUTTON_L_EVENT_SET_PUSH",
  "BUTTON_L_EVENT_SET_RELEASE",
  "BUTTON_L_EVENT_UP_PUSH",
  "BUTTON_L_EVENT_UP_RELEASE",
  "BUTTON_L_EVENT_DOWN_PUSH",
  "BUTTON_L_EVENT_DOWN_RELEASE",
  "BUTTON_L_EVENT_LONG_SET",
};


void test_timer_handler(void *p_data)
{
    trace_debug("test_timer_handler\n\r");
}

static void r_adc_button_handler(adc_button_event_e event)
{
    trace_debug("r_adc_button_handler event = %s\n\r",mp_button[event]);
}

static void l_adc_button_handler(adc_button_event_e event)
{
    trace_debug("l_adc_button_handler event = %s\n\r",mp_button[event]);
}

static void app_evt_schedule(void * p_event_data)
{
    trace_debug("app_evt_schedule\n\r");
}



uint8_t Ht1621Tab[] = {0x00, 0x00, 0x00, 0x00};

int main(void)
{
  int err_code = 0;

  trace_init();

  /*greeting*/
  trace_debug("\n\r\n\r");
  trace_debug("       *** Welcome to the Project ***\n\r");
  trace_debug("\n\r");

  TIMER_INIT();
  trace_debug("TIMER_INIT done\n\r");

  TIMER_CREATE(&m_test_timer,false,false,test_timer_handler);
//  TIMER_START(m_test_timer, 1000);

  /**
   * delay 函数的初始化
   */
  mid_system_tick_init();

  ir_tx_init();

  adc_init();
  l_adc_button_event_handler_register(l_adc_button_handler);
  r_adc_button_event_handler_register(r_adc_button_handler);

  bk9532_lr_init();
  ad22650_lr_init();

  HT1621_Init();
  HT1621_WriteAllData(0, Ht1621Tab, 16); //清除LCD显示数据

  delay_ms(10);
//  Display();

#if 0
  /**
   * flash test
   */
  uint8_t w_data[4] = {1,2,3,4};
  uint8_t r_data[4] = {0};

  err_code = mid_flash_read(FLASH_APP_PARAM_ADDRESS, 4, r_data);
  if(err_code)
  {
      trace_error("ft_flash_read error %d\n\r",err_code);
  }
  delay_ms(100);

  trace_error("read address 0x%08x:\n\r",FLASH_APP_PARAM_ADDRESS);
  trace_dump(r_data,4);

  err_code = mid_flash_write(FLASH_APP_PARAM_ADDRESS, 4, (uint32_t *)w_data);
  if(err_code)
  {
      trace_error("ft_flash_write error %d\n\r",err_code);
  }
  delay_ms(100);

  err_code = mid_flash_read(FLASH_APP_PARAM_ADDRESS, 4, r_data);
  if(err_code)
  {
      trace_error("ft_flash_read error %d\n\r",err_code);
  }
  delay_ms(100);
  trace_error("read address 0x%08x:\n\r",FLASH_APP_PARAM_ADDRESS);
  trace_dump(r_data,4);

#endif

#if 0
  err_code = ir_tx_start(data, sizeof(data));
  if(err_code)
  {
    trace_error("ir_tx_start error %d\n\r",err_code);
  }
#endif

  APP_SCHED_INIT(&m_app_scheduler, SCHED_MAX_EVENT_DATA_SIZE, SCHED_QUEUE_SIZE);

  app_sched_event_put(&m_app_scheduler, NULL, 0, app_evt_schedule);


  trace_info("Start loop\n\r");
  while(1)
  {
      app_sched_execute(&m_app_scheduler);
      adc_button_loop_task();
      mid_timer_loop_task();
      bk953x_loop_task();
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif




