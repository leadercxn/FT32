#include "main.h"
#include "develop_lib.h"
#include "ft_usart.h"
#include "shell_port.h"
#include "shell.h"

static void delay(uint32_t n)
{
  uint16_t i = 0;
  uint16_t j = 0;

  for (i = 0; i < 300; i++)
  {
    for (j = 0; j < n; j++)
      ;
  }
}

void timer_handler(void)
{
  static uint16_t cnt = 0;

  cnt++;

  if (cnt > 2000)
  {
    cnt = 0;
  }

  if (cnt > 1000)
  {
    set_gpio_value(GPIOB, GPIO_Pin_1, 1);
  }
  else
  {
    set_gpio_value(GPIOB, GPIO_Pin_1, 0);
  }
}

int main(void)
{

  // timer_init();

  // timer_handler_register(timer_handler);

  // conf_gpio_output(RCC_AHBPeriph_GPIOB, GPIOB, GPIO_Pin_1);

  ControlUartInit(UART2_CHANNEL, 115200);
  userShellInit();

  while (1)
  {
    userShellRun();
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
