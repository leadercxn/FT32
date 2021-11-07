#include "main.h"
#include "develop_lib.h"

#include "bk953x_handler.h"

void timer_handler(void)
{
    static uint16_t cnt = 0;

    cnt ++;

    if(cnt > 1000)
    {
        cnt = 0;
    }

    if(cnt > 500)
    {
        set_gpio_value(GPIOA, GPIO_Pin_12,1);
    }
    else
    {
        set_gpio_value(GPIOA, GPIO_Pin_12,0);
    }

}

int main(void)
{
  uint16_t adc_value = 0;
  trace_init();
  timer_init();

  bk9532_lr_init();

  //timer15_pwm_ch1_init();
  //timer_handler_register(timer_handler);

  //conf_gpio_output(RCC_AHBPeriph_GPIOA, GPIOA, GPIO_Pin_12);

  exit_init();
  adc_init();

  trace_info("Start loop\n\r");
  while(1)
  {
      #if 0
      set_gpio_value(GPIOA , GPIO_Pin_12 ,0);
      delay_ms(100);
      set_gpio_value(GPIOA , GPIO_Pin_12 ,1);
      delay_ms(100);
      #endif

      adc_value = adc_ch_value_get(0);
      trace_debug("adc_value = %d\n\r",adc_value);

      ft_delay_ms(1000);
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




