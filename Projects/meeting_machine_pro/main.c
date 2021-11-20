#include "board_config.h"

#include "bk953x_handler.h"
#include "adc_button_handler.h"

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

int main(void)
{
  trace_init();

  /*greeting*/
  trace_debug("\n\r\n\r");
  trace_debug("       *** Welcome to the Project ***\n\r");
  trace_debug("\n\r");

  TIMER_INIT();
  trace_debug("TIMER_INIT done\n\r");

  TIMER_CREATE(&m_test_timer,false,true,test_timer_handler);
//  trace_debug("mid_timer_create\n\r");

  ir_tx_init();

  adc_init();

  l_adc_button_event_handler_register(l_adc_button_handler);
  r_adc_button_event_handler_register(r_adc_button_handler);


//  TIMER_START(m_test_timer,500);
  bk9532_lr_init();

#if 0
  err_code = ir_tx_start(data, sizeof(data));
  if(err_code)
  {
    trace_error("ir_tx_start error %d\n\r",err_code);
  }
#endif
  
  trace_info("Start loop\n\r");
  while(1)
  {
      adc_button_loop_task();
//      delay_ms(200);
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




