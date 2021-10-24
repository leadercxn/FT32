#ifndef __FT_I2C_H
#define __FT_I2C_H


#define I2C1_TIMING                 0xF0210507	//when =SYSCLK=48MHZ

#define I2C1_CLK                      RCC_APB1Periph_I2C1
   
#define I2C1_SCL_PIN                  GPIO_Pin_6                  /* PB.06 */
#define I2C1_SCL_GPIO_PORT            GPIOB                       /* GPIOB */
#define I2C1_SCL_GPIO_CLK             RCC_AHBPeriph_GPIOB
#define I2C1_SCL_SOURCE               GPIO_PinSource6
#define I2C1_SCL_AF                   GPIO_AF_1

#define I2C1_SDA_PIN                  GPIO_Pin_7                  /* PB.07 */
#define I2C1_SDA_GPIO_PORT            GPIOB                       /* GPIOB */
#define I2C1_SDA_GPIO_CLK             RCC_AHBPeriph_GPIOB
#define I2C1_SDA_SOURCE               GPIO_PinSource7
#define I2C1_SDA_AF                   GPIO_AF_1



#define VIRT_SCL_PIN                  GPIO_Pin_12                  /* 模拟I2C-SCL */
#define VIRT_SCL_GPIO_PORT            GPIOA                       /* GPIOA */
#define VIRT_SCL_GPIO_CLK             RCC_AHBPeriph_GPIOA


#define VIRT_SDA_PIN                  GPIO_Pin_11                  /* 模拟I2C-SDA */
#define VIRT_SDA_GPIO_PORT            GPIOA                       /* GPIOA */
#define VIRT_SDA_GPIO_CLK             RCC_AHBPeriph_GPIOA



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

