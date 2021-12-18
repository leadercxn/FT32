#include "board_config.h"

#include "bk953x_handler.h"

#define SCHED_MAX_EVENT_DATA_SIZE   8
#define SCHED_QUEUE_SIZE            20

static app_scheduler_t  m_app_scheduler;

uint8_t ir_rx_data[4] = {0};
uint8_t ir_rx_len = 0;

static void app_evt_schedule(void * p_event_data)
{
    trace_debug("app_evt_schedule\n\r");
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

  APP_SCHED_INIT(&m_app_scheduler, SCHED_MAX_EVENT_DATA_SIZE, SCHED_QUEUE_SIZE);
  app_sched_event_put(&m_app_scheduler, NULL, 0, app_evt_schedule);

  bk9531_init();

  ir_rx_init();

  trace_info("Start loop\n\r");
  while(1)
  {
    app_sched_execute(&m_app_scheduler);

    bk953x_loop_task();

//    ir_rx_len = ir_rx_decode_result_get(ir_rx_data);


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


