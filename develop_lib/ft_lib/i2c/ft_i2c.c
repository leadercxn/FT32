#include "ft32f0xx.h"
#include "ft_i2c.h"
#include "util.h"
#include "stdbool.h"


/**
  * @brief  Initializes the I2C source clock and IOs used to drive.
  * @param  None
  * @retval None
  */
void i2c1_res_init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* Configure the I2C clock source. The clock is derived from the HSI */
    RCC_I2CCLKConfig(RCC_I2C1CLK_SYSCLK);	//RCC_I2C1CLK_SYSCLK	RCC_I2C1CLK_HSI
        
    /* io port clock enable */
    RCC_AHBPeriphClockCmd(I2C1_SCL_GPIO_CLK | I2C1_SDA_GPIO_CLK, ENABLE);
    
    /* i2c1 Periph clock enable */
    RCC_APB1PeriphClockCmd(I2C1_CLK, ENABLE);
    
    /* Connect PXx to I2C_SCL*/
    GPIO_PinAFConfig(I2C1_SCL_GPIO_PORT, I2C1_SCL_SOURCE, I2C1_SCL_AF);
    
    /* Connect PXx to I2C_SDA*/
    GPIO_PinAFConfig(I2C1_SDA_GPIO_PORT, I2C1_SDA_SOURCE, I2C1_SDA_AF);

    /* GPIO configuration */  
    /* Configure i2c1 pins: SCL */
    GPIO_InitStructure.GPIO_Pin =   I2C1_SCL_PIN;
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd =  GPIO_PuPd_UP;
    GPIO_Init(I2C1_SCL_GPIO_PORT, &GPIO_InitStructure);
    
    /* Configure i2c1 pins: SDA */
    GPIO_InitStructure.GPIO_Pin = I2C1_SDA_PIN;
    GPIO_Init(I2C1_SDA_GPIO_PORT, &GPIO_InitStructure);



    I2C_InitTypeDef  I2C_InitStructure;

    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_AnalogFilter = I2C_AnalogFilter_Enable;
    I2C_InitStructure.I2C_DigitalFilter = 0x00;
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_Timing = I2C1_TIMING;

    /* Apply I2C1 configuration after enabling it */
    I2C_Init(I2C1, &I2C_InitStructure);
   
    /* I2C1 Peripheral Enable */
    I2C_Cmd(I2C1, ENABLE);
}

void i2c1_res_deinit(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure; 

    /* I2C1 Peripheral Disable */
    I2C_Cmd(I2C1, DISABLE);

    /* I2C1 DeInit */
    I2C_DeInit(I2C1);

    /* I2C1 Periph clock disable */
    RCC_APB1PeriphClockCmd(I2C1_CLK, DISABLE);

    /* Configure I2C1 pins: SCL */
    GPIO_InitStructure.GPIO_Pin = I2C1_SCL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(I2C1_SCL_GPIO_PORT, &GPIO_InitStructure);

    /* Configure I2C1 pins: SDA */
    GPIO_InitStructure.GPIO_Pin = I2C1_SDA_PIN;
    GPIO_Init(I2C1_SDA_GPIO_PORT, &GPIO_InitStructure);
}




