#ifndef __IR_RX_DECODE_H
#define __IR_RX_DECODE_H

void ir_rx_init(void);
uint8_t ir_rx_decode_result_get(uint8_t *p_data);
#endif
