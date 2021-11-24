#include "ft32f0xx.h"
#include "ft_usart.h"
#include "util.h"
#include "stdbool.h"

#include "trace.h"

#ifdef TRACE_ENABLE

/**
 * @brief Definition for COM port1, connected to USART2
 */
void trace_init(void)
{

#ifdef FT32F072x8
// ControlUartInit(UART2_CHANNEL, 115200);
#else
    ControlUartInit(UART1_CHANNEL, 115200);
#endif
}

void trace_dump(void *p_buffer, uint32_t len)
{
    uint8_t *p = (uint8_t *)p_buffer;

    for (uint32_t index = 0; index < len; index++)
    {
        TRACE_PRINTF("%02X", p[index]);
    }

    TRACE_PRINTF("\r\n");
}

#endif // TRACE_ENABLE
