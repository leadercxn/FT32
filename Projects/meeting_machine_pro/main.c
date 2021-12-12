#include "board_config.h"

#include "bk953x_handler.h"
#include "adc_button_handler.h"
#include "ad22650_handler.h"
#include "flash_handler.h"
#include "lcd_display_handler.h"

#define SCHED_MAX_EVENT_DATA_SIZE   8
#define SCHED_QUEUE_SIZE            20

static app_scheduler_t  m_app_scheduler;

uint8_t data[4] = {0x64, 0x23, 0x18, 0x74};

/**
 * 供电开关状态
 */
uint8_t g_sys_power_on = 1;
uint8_t g_old_sys_power_on = 1;

static gpio_object_t   m_sys_power_sw_gpio = 
                {
                    .gpio_port_periph_clk = SYS_POWER_SWITCH_PORT_PERIPH_CLK,
                    .p_gpio_port = SYS_POWER_SWITCH_PORT,
                    .gpio_dir = GPIO_DIR_INPUT,
                    .gpio_pin = SYS_POWER_SWITCH_PIN,
                };

static char * mp_button[BUTTON_EVENT_MAX] = 
{
  "BUTTON_R_EVENT_SET_PUSH",
  "BUTTON_R_EVENT_SET_RELEASE",
  "BUTTON_R_EVENT_LONG_SET",

  "BUTTON_R_EVENT_UP_PUSH",
  "BUTTON_R_EVENT_UP_RELEASE",
  "BUTTON_R_EVENT_DOWN_PUSH",
  "BUTTON_R_EVENT_DOWN_RELEASE",
  

  "BUTTON_L_EVENT_SET_PUSH",
  "BUTTON_L_EVENT_SET_RELEASE",
  "BUTTON_L_EVENT_LONG_SET",

  "BUTTON_L_EVENT_UP_PUSH",
  "BUTTON_L_EVENT_UP_RELEASE",
  "BUTTON_L_EVENT_DOWN_PUSH",
  "BUTTON_L_EVENT_DOWN_RELEASE",
};

/**
 * @brief 右侧adc按键回调
 */
static void r_adc_button_handler(adc_button_event_e event)
{
    uint16_t r_index = 0;

    static uint64_t pre_ticks = 0;
    uint64_t now_ticks = mid_timer_ticks_get();

    /**
     * 两个时间得间隔200ms
     */
    if((now_ticks - pre_ticks > 200) || (event == BUTTON_R_EVENT_SET_RELEASE))
    {
      pre_ticks = now_ticks;
    }
    else
    {
      return;
    }

    trace_debug("r_adc_button_handler event = %s\n\r",mp_button[event]);

    /**
     * 上下按键
     */
    if((event >= BUTTON_R_EVENT_UP_PUSH) && (event <= BUTTON_R_EVENT_DOWN_RELEASE))
    {
        r_index = channel_index_lr_get(SCREEN_R);
        /* 右边 */
        if((BUTTON_R_EVENT_UP_RELEASE == event) || (BUTTON_R_EVENT_UP_PUSH == event))
        {
          r_index += 1;

          if(r_index > SCREEN_R_CHANNEL_INDEX_MAX)
          {
            r_index = SCREEN_R_CHANNEL_INDEX_MIN;
          }
        }
        else
        {
          r_index -= 1;

          if(r_index < SCREEN_R_CHANNEL_INDEX_MIN)
          {
            r_index = SCREEN_R_CHANNEL_INDEX_MAX;
          }
        }

        channel_index_lr_set(SCREEN_R, r_index);
    }

    /**
     * SET
     */
    if(event == BUTTON_R_EVENT_SET_RELEASE)
    {
        if(R_SETTING_MODE != channel_settings_mode_get())
        {
            channel_settings_mode_set(R_SETTING_MODE);
        }
        else
        {
            channel_settings_mode_set(EXIT_SET_MODE);
        }
    }

    /**
     * LONG_SET
     */

}

/**
 * @brief 左侧adc按键回调
 */
static void l_adc_button_handler(adc_button_event_e event)
{
    uint16_t l_index = 0;

    static uint64_t pre_ticks = 0;

    uint64_t now_ticks = mid_timer_ticks_get();

    /**
     * 两个时间得间隔200ms
     */
    if((now_ticks - pre_ticks > 200) || (event == BUTTON_L_EVENT_SET_RELEASE))
    {
      pre_ticks = now_ticks;
    }
    else
    {
      return;
    }

    trace_debug("l_adc_button_handler event = %s\n\r",mp_button[event]);

    /* 左边 */
    if((event >= BUTTON_L_EVENT_UP_PUSH) && (event <= BUTTON_L_EVENT_DOWN_RELEASE))
    {
        l_index = channel_index_lr_get(SCREEN_L);

        if((BUTTON_L_EVENT_UP_RELEASE == event)||(BUTTON_L_EVENT_UP_PUSH == event))
        {
          l_index += 1;

          if(l_index > SCREEN_L_CHANNEL_INDEX_MAX)
          {
            l_index = SCREEN_L_CHANNEL_INDEX_MIN;
          }
        }
        else
        {
          l_index -= 1;

          if(l_index < SCREEN_L_CHANNEL_INDEX_MIN)
          {
            l_index = SCREEN_L_CHANNEL_INDEX_MAX;
          }
        }
      
        channel_index_lr_set(SCREEN_L, l_index);
    }

    /**
     * SET
     */
    if(event == BUTTON_L_EVENT_SET_RELEASE)
    {
        if(L_SETTING_MODE != channel_settings_mode_get())
        {
            channel_settings_mode_set(L_SETTING_MODE);
        }
        else
        {
            channel_settings_mode_set(EXIT_SET_MODE);
        }
    }

    /**
     * LONG_SET
     */
}

static void app_evt_schedule(void * p_event_data)
{
    trace_debug("app_evt_schedule\n\r");
}

/**
 * @brief 参数初始化
 */
static void app_param_init(void)
{
    channel_index_lr_set(SCREEN_L, g_app_param.l_ch_index);
    channel_index_lr_set(SCREEN_R, g_app_param.r_ch_index);
}

static void sys_power_sw_handler(void)
{
    gpio_input_get(&m_sys_power_sw_gpio, &g_sys_power_on);
    
    if(g_old_sys_power_on != g_sys_power_on)
    {
        if(g_sys_power_on)
        {
          lcd_off_status_set(true);
        }
        else
        {
          lcd_off_status_set(false);
        }

        g_old_sys_power_on = g_sys_power_on;
    }
}

int main(void)
{
  int err_code = 0;

  trace_init();

  /*greeting*/
  trace_info("\n\r\n\r");
  trace_info("       *** Welcome to the Project ***\n\r");
  trace_info("\n\r");

  TIMER_INIT();

  /**
   * delay 函数的初始化
   */
  mid_system_tick_init();

  app_param_flash_init();
  app_param_init();

  /* 提前初始化lcd硬件，预防上次掉电后马上插上，会显示旧数据 */
  lcd_hw_init();

  gpio_config(&m_sys_power_sw_gpio);
  do
  {
      lcd_black_light_enable(false);    //  关掉LCD显示
      lcd_ctrl_enable(false);
      delay_ms(50);
      gpio_input_get(&m_sys_power_sw_gpio, &g_sys_power_on);
      g_old_sys_power_on = g_sys_power_on;
  } while(g_sys_power_on);
  trace_info("Power On\n\r");
  
  lcd_display_init();

  ir_tx_init();

  adc_init();
  l_adc_button_event_handler_register(l_adc_button_handler);
  r_adc_button_event_handler_register(r_adc_button_handler);

  bk9532_lr_init();
  ad22650_lr_init();


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
    lcd_display_loop_task();
    sys_power_sw_handler();
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




