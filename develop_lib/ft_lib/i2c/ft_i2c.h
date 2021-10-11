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

#endif

