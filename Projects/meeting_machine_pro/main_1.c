#include "board_config.h"

#include "bk953x_handler.h"
#include "adc_button_handler.h"
#include "ad22650_handler.h"
#include "flash_handler.h"
#include "board_ht1621.h"
#include "ht1621_display.h"
#include "ht1621.h"

#include "ft32f0xx.h"

static void SysTickConfig(void);
static void gpioConfig(void);
/**
  * @brief  Configure a SysTick Base time to 10 ms.
  * @param  None
  * @retval None
  */
static void SysTickConfig(void)
{
  /* Setup SysTick Timer for 10ms interrupts  */
  if (SysTick_Config(SystemCoreClock / 100))
  {
    /* Capture error */
    while (1)
      ;
  }

  /* Configure the SysTick handler priority */
  NVIC_SetPriority(SysTick_IRQn, 0x0);
}

/*********************************************************************
 * LOCAL FUNCTIONS
 */
/**
 @brief 引脚初始化
 @param 无
 @return 无
*/
void gpioConfig(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* GPIOA Periph clock enable */
  RCC_AHBPeriphClockCmd(HT1621_CS_CLK | HT1621_DATA_CLK | HT1621_WR_CLK, ENABLE);

  /* Enable SYSCFG clock  */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  GPIO_InitStructure.GPIO_Pin = HT1621_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(HT1621_CS_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = HT1621_DATA_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(HT1621_DATA_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = HT1621_WR_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(HT1621_WR_PORT, &GPIO_InitStructure);
}

int main(void)
{
  int err_code = 0;

  trace_init();

  /*greeting*/
  trace_debug("\n\r\n\r");
  trace_debug("       *** Welcome to the Project ***\n\r");
  trace_debug("\n\r");

  // gpioConfig();
  // /* SysTick configuration ---------------------------------------------------*/
  // SysTickConfig();

  // HT1621_Init();
  // HT1621_WriteData4Bit(TEMP_ADDR, 0x00);                             // ℃灭
  // HT1621_WriteData4Bit(SIGNAL_ADDR, 0x00);                           // 信号灭
  // HT1621_WriteData4Bit(FM_SOUND_1_ADDR, DISPLAY_ALARM | DISPLAY_FM); // 报警+FM亮
  // HT1621_WriteData8Bit(FOURTH_8_MHz_ADDR, DISPLAY_MHZ);              // MHz亮

  // LCD_ShowFrequency(100000);

  SysTickConfig();
  ht1621_init();

  lcd_init();
  Display_Wendu_1(2, 25);

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
