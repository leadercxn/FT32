#include "main.h"
#include "develop_lib.h"

static void delay(uint32_t n)
{
    uint16_t i = 0;
    uint16_t j = 0;

    for(i = 0; i < 300; i ++)
    {
        for(j = 0; j < n; j++);
    }
}

int main(void)
{
#if 0
    conf_gpio_output(RCC_AHBPeriph_GPIOB, GPIOB, GPIO_Pin_1);
    while (1)
    {
        set_gpio_value(GPIOB, GPIO_Pin_1,1);
        delay(5000);
        set_gpio_value(GPIOB, GPIO_Pin_1,0);
        delay(5000);
    }
#endif

  conf_whole_gpios_output(RCC_AHBPeriph_GPIOC, GPIOC, 0xff);
  while (1)
  {
      //set_gpio_value(GPIOB, GPIO_Pin_1,1);
      set_halt_gpios_value(GPIOC ,0xff, true);
      delay(5000);
      //set_gpio_value(GPIOB, GPIO_Pin_1,0);
      set_halt_gpios_value(GPIOC ,0x00, true);
      delay(5000);
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




