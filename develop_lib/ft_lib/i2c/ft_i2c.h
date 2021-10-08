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






#endif

