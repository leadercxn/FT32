#include "main.h"
#include "develop_lib.h"
#include "lib_error.h"
#include "bk953x_handler.h"
#include "adc_button_handler.h"

MID_TIMER_DEF(m_test_timer);
uint8_t data[4] = { 0x64,0x23,0x18,0x74 };

static bool m_is_high = true;

void test_timer_handler(void *p_data)
{
    //trace_debug("test_timer_handler\n\r");
    if(m_is_high)
    {
      m_is_high = false;
      set_gpio_value(GPIOB , GPIO_Pin_0 ,0);
    }
    else
    {
      m_is_high = true;
      set_gpio_value(GPIOB , GPIO_Pin_0 ,1);
    }
}

int main(void)
{
  int err_code = ENONE;
  uint16_t adc_value = 0;
  trace_init();

  TIMER_INIT();
  trace_debug("mid_timer_init\n\r");

  TIMER_CREATE(&m_test_timer,false,true,test_timer_handler);
//  trace_debug("mid_timer_create\n\r");

  ir_tx_init();
//  ir_rx_init();

  adc_init();

//  TIMER_START(m_test_timer,500);
  conf_gpio_output(RCC_AHBPeriph_GPIOB, GPIOB, GPIO_Pin_0);
  conf_gpio_output(RCC_AHBPeriph_GPIOA, GPIOA, GPIO_Pin_8);

  //复位要适当的延时，别太快
  set_gpio_value(GPIOB , GPIO_Pin_0 ,0);
  set_gpio_value(GPIOA , GPIO_Pin_8 ,0);
  delay_ms(50);
  set_gpio_value(GPIOB , GPIO_Pin_0 ,1);
  set_gpio_value(GPIOA , GPIO_Pin_8 ,1);
  delay_ms(50);

  bk9532_lr_init();

  trace_info("Start loop\n\r");
#if 0
  err_code = ir_tx_start(data, sizeof(data));
  if(err_code)
  {
    trace_error("ir_tx_start error %d\n\r",err_code);
  }
#endif
  
  while(1)
  {
      adc_button_loop_task();
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




