#ifndef __FT_I2C_H
#define __FT_I2C_H


typedef void (*i2c_transfer_timeout_handler_t) (void);

void i2c_transfer_timeout_handler_register(i2c_transfer_timeout_handler_t handler);

void i2c1_res_init(void);

void i2c1_res_deinit(void);

int i2c1_write_one_byte(uint8_t slaver_addr, uint8_t reg, uint8_t data);

int i2c1_read_one_byte(uint8_t slaver_addr, uint8_t reg, uint8_t *p_data);



void virt_i2c_init(void);

void virt1_i2c_start(void);
void virt1_i2c_stop(void);
int virt1_i2c_wait_ack(void);
void virt1_i2c_set_ack(void);
void virt1_i2c_set_nack(void);
void virt1_i2c_send_byte(uint8_t byte);
uint8_t virt1_i2c_read_byte(bool ack);

void virt1_i2c_write_one_byte(uint8_t slaver_addr, uint8_t reg, uint8_t data);

void virt1_i2c_read_one_byte(uint8_t slaver_addr, uint8_t reg, uint8_t *p_data);

#endif

