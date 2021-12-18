#include "stddef.h"
#include "stdbool.h"

#include "board_config.h"
#include "ft_i2c.h"

static i2c_transfer_timeout_handler_t m_i2c_transfer_timeout_handler = NULL;

#if 0
/**
  * @brief  i2c1 资源、IO初始化
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

/**
  * @brief  i2c1 资源、IO释放
  * @param  None
  * @retval None
  */
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

/**
 * 
 */
void i2c_transfer_timeout_handler_register(i2c_transfer_timeout_handler_t handler)
{
    m_i2c_transfer_timeout_handler = handler;
}

/**
 * @brief i2c1往从设备指定的寄存器写入1字节数据
 * 
 * 模式: 从设备地址+寄存器地址+数据(1B)
 */
int i2c1_write_one_byte(uint8_t slaver_addr, uint8_t reg, uint8_t data)
{
    uint16_t time_out = I2C_TRANFS_TIMEOUT;

    /**
     * 配置CR2寄存器
     * 
     * 发送一次从设备的地址
     */
    I2C_TransferHandling(I2C1, slaver_addr, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);

    /* 获取发送完成状态 */
    while(I2C_GetFlagStatus(I2C1, I2C_ISR_TXIS) == RESET)
    {
        if((time_out--) == 0)
        {
            if(m_i2c_transfer_timeout_handler)
            {
                m_i2c_transfer_timeout_handler();
            }

            return -EIO;
        }
    }

    /**发送要读寄存器的地址*/
    I2C_SendData(I2C1, reg);

    time_out = I2C_TRANFS_TIMEOUT;
    /* 获取发送完成状态 */
    while(I2C_GetFlagStatus(I2C1, I2C_ISR_TC) == RESET)
    {
        if((time_out--) == 0)
        {
            if(m_i2c_transfer_timeout_handler)
            {
                m_i2c_transfer_timeout_handler();
            }

            return -EIO;
        }
    }

    /* 发送数据 */  
    I2C_SendData(I2C1, data);
    time_out = I2C_TRANFS_TIMEOUT;
    /* 获取发送完成状态 */
    while(I2C_GetFlagStatus(I2C1, I2C_ISR_TC) == RESET)
    {
        if((time_out--) == 0)
        {
            if(m_i2c_transfer_timeout_handler)
            {
                m_i2c_transfer_timeout_handler();
            }

            return -EIO;
        }
    }

    /**
     * 产生stop
     */
    I2C_GenerateSTOP(I2C1, ENABLE);

    return ENONE;
}


/**
 * @brief i2c1往从设备指定的寄存器读出1字节数据
 * 
 * 模式: 从设备地址+寄存器地址+开始+从设备地址+数据(1B)
 */
int i2c1_read_one_byte(uint8_t slaver_addr, uint8_t reg, uint8_t *p_data)
{
    uint16_t time_out = I2C_TRANFS_TIMEOUT;

    /**
     * 配置CR2寄存器
     * 
     * 发送一次从设备的地址
     */
    I2C_TransferHandling(I2C1, slaver_addr, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);

    /* 获取发送完成状态 */
    while(I2C_GetFlagStatus(I2C1, I2C_ISR_TXIS) == RESET)
    {
        if((time_out--) == 0)
        {
            if(m_i2c_transfer_timeout_handler)
            {
                m_i2c_transfer_timeout_handler();
            }

            return -EIO;
        }
    }

    /**
     * 发送要读寄存器的地址
     */
    I2C_SendData(I2C1, reg);

    time_out = I2C_TRANFS_TIMEOUT;
    /* 获取发送完成状态 */
    while(I2C_GetFlagStatus(I2C1, I2C_ISR_TC) == RESET)
    {
        if((time_out--) == 0)
        {
            if(m_i2c_transfer_timeout_handler)
            {
                m_i2c_transfer_timeout_handler();
            }

            return -EIO;
        }
    }

    /* 判断是否有未完成的接收 */
    time_out = I2C_TRANFS_TIMEOUT;
    while(I2C_GetFlagStatus(I2C1, I2C_ISR_TCR) == RESET)
    {
        if((time_out--) == 0)
        {
            if(m_i2c_transfer_timeout_handler)
            {
                m_i2c_transfer_timeout_handler();
            }

            return -EIO;
        }
    }

    I2C_TransferHandling(I2C1, slaver_addr, 1, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);

    /* 等待接收到的数据 */
    time_out = I2C_TRANFS_TIMEOUT;
    while(I2C_GetFlagStatus(I2C1, I2C_ISR_RXNE) == RESET)
    {
        if((time_out--) == 0)
        {
            if(m_i2c_transfer_timeout_handler)
            {
                m_i2c_transfer_timeout_handler();
            }

            return -EIO;
        }
    }

    *p_data = I2C_ReceiveData(I2C1);

    /* 等待stop信号 */
    time_out = I2C_TRANFS_TIMEOUT;
    while(I2C_GetFlagStatus(I2C1, I2C_ISR_STOPF) == RESET)
    {
        if((time_out--) == 0)
        {
            if(m_i2c_transfer_timeout_handler)
            {
                m_i2c_transfer_timeout_handler();
            }

            return -EIO;
        }
    }

    I2C_ClearFlag(I2C1, I2C_ICR_STOPCF);

    return ENONE;
}

#endif



/**
 * @brief 做一个简单的延时
 */
static void ft_i2c_delay(void)
{
    uint8_t i;
    for(i = 0; i < 4; i++);
}



/* 
 * 
 * summary 
 * 
 * */
void ft_virt_i2c_init(ft_virt_i2c_t *p_virt_i2c)
{
    if(!p_virt_i2c)
    {
        trace_error("p_virt_i2c is NULL\n\r");
        return;
    }

    conf_gpio_output(p_virt_i2c->scl_port_periph_clk, p_virt_i2c->p_scl_gpio_port, p_virt_i2c->scl_gpio_pin);
    set_gpio_value(p_virt_i2c->p_scl_gpio_port, p_virt_i2c->scl_gpio_pin, 1);

    conf_gpio_output(p_virt_i2c->sda_port_periph_clk, p_virt_i2c->p_sda_gpio_port, p_virt_i2c->sda_gpio_pin);
    set_gpio_value(p_virt_i2c->p_sda_gpio_port, p_virt_i2c->sda_gpio_pin, 1);
}

void ft_virt_i2c_start(ft_virt_i2c_t *p_virt_i2c)
{
    if(!p_virt_i2c)
    {
        return;
    }

    conf_gpio_output(p_virt_i2c->sda_port_periph_clk, p_virt_i2c->p_sda_gpio_port, p_virt_i2c->sda_gpio_pin);
    set_gpio_value(p_virt_i2c->p_sda_gpio_port, p_virt_i2c->sda_gpio_pin, 1);
    set_gpio_value(p_virt_i2c->p_scl_gpio_port, p_virt_i2c->scl_gpio_pin, 1);

    ft_i2c_delay();
    set_gpio_value(p_virt_i2c->p_sda_gpio_port, p_virt_i2c->sda_gpio_pin, 0);

    ft_i2c_delay();
    set_gpio_value(p_virt_i2c->p_scl_gpio_port, p_virt_i2c->scl_gpio_pin, 0);
}

void ft_virt_i2c_stop(ft_virt_i2c_t *p_virt_i2c)
{
    if(!p_virt_i2c)
    {
        return;
    }

    conf_gpio_output(p_virt_i2c->sda_port_periph_clk, p_virt_i2c->p_sda_gpio_port, p_virt_i2c->sda_gpio_pin);
    set_gpio_value(p_virt_i2c->p_sda_gpio_port, p_virt_i2c->sda_gpio_pin, 0);
    set_gpio_value(p_virt_i2c->p_scl_gpio_port, p_virt_i2c->scl_gpio_pin, 0);

    ft_i2c_delay();
    set_gpio_value(p_virt_i2c->p_scl_gpio_port, p_virt_i2c->scl_gpio_pin, 1);
    ft_i2c_delay();
    set_gpio_value(p_virt_i2c->p_sda_gpio_port, p_virt_i2c->sda_gpio_pin, 1);
}

int ft_virt_i2c_wait_ack(ft_virt_i2c_t *p_virt_i2c)
{
    uint8_t timeout = 0;
    uint8_t sda_value = 0;

    if(!p_virt_i2c)
    {
        return -EINVAL;
    }
    
    conf_gpio_input(p_virt_i2c->sda_port_periph_clk, p_virt_i2c->p_sda_gpio_port, p_virt_i2c->sda_gpio_pin, GPIO_PuPd_UP);

    set_gpio_value(p_virt_i2c->p_scl_gpio_port, p_virt_i2c->scl_gpio_pin, 1);
    ft_i2c_delay();

    get_gpio_value(p_virt_i2c->p_sda_gpio_port, p_virt_i2c->sda_gpio_pin, &sda_value);
    while(sda_value)
    {
        timeout++;
        if(timeout > 250)
        {
            ft_virt_i2c_stop(p_virt_i2c);
            return -EIO;
        }

        get_gpio_value(p_virt_i2c->p_sda_gpio_port, p_virt_i2c->sda_gpio_pin, &sda_value);
        ft_i2c_delay();
    }

    set_gpio_value(p_virt_i2c->p_scl_gpio_port, p_virt_i2c->scl_gpio_pin, 0);

    return ENONE;
}

void ft_virt_i2c_set_ack(ft_virt_i2c_t *p_virt_i2c)
{
    if(!p_virt_i2c)
    {
        return;
    }

    set_gpio_value(p_virt_i2c->p_scl_gpio_port, p_virt_i2c->scl_gpio_pin, 0);
    conf_gpio_output(p_virt_i2c->sda_port_periph_clk, p_virt_i2c->p_sda_gpio_port, p_virt_i2c->sda_gpio_pin);
    set_gpio_value(p_virt_i2c->p_sda_gpio_port, p_virt_i2c->sda_gpio_pin, 0);

    ft_i2c_delay();

    set_gpio_value(p_virt_i2c->p_scl_gpio_port, p_virt_i2c->scl_gpio_pin, 1);
    ft_i2c_delay();
    set_gpio_value(p_virt_i2c->p_scl_gpio_port, p_virt_i2c->scl_gpio_pin, 0);
}

void ft_virt_i2c_set_nack(ft_virt_i2c_t *p_virt_i2c)
{
    if(!p_virt_i2c)
    {
        return;
    }

    set_gpio_value(p_virt_i2c->p_scl_gpio_port, p_virt_i2c->scl_gpio_pin, 0);
    conf_gpio_output(p_virt_i2c->sda_port_periph_clk, p_virt_i2c->p_sda_gpio_port, p_virt_i2c->sda_gpio_pin);
    set_gpio_value(p_virt_i2c->p_sda_gpio_port, p_virt_i2c->sda_gpio_pin, 1);

    ft_i2c_delay();

    set_gpio_value(p_virt_i2c->p_scl_gpio_port, p_virt_i2c->scl_gpio_pin, 1);
    ft_i2c_delay();
    set_gpio_value(p_virt_i2c->p_scl_gpio_port, p_virt_i2c->scl_gpio_pin, 0);
}

void ft_virt_i2c_send_byte(ft_virt_i2c_t *p_virt_i2c, uint8_t byte)
{
    uint8_t i = 0;
    uint8_t temp = 0;

    conf_gpio_output(p_virt_i2c->sda_port_periph_clk, p_virt_i2c->p_sda_gpio_port, p_virt_i2c->sda_gpio_pin);
    set_gpio_value(p_virt_i2c->p_scl_gpio_port, p_virt_i2c->scl_gpio_pin, 0);

    for(i = 0; i < 8; i++)
    {
        temp = (byte & 0x80) >> 7;

        set_gpio_value(p_virt_i2c->p_sda_gpio_port, p_virt_i2c->sda_gpio_pin, temp);
        ft_i2c_delay();
        set_gpio_value(p_virt_i2c->p_scl_gpio_port, p_virt_i2c->scl_gpio_pin, 1);
        ft_i2c_delay();
        set_gpio_value(p_virt_i2c->p_scl_gpio_port, p_virt_i2c->scl_gpio_pin, 0);
        ft_i2c_delay();

        byte <<= 1;
    }

    set_gpio_value(p_virt_i2c->p_sda_gpio_port, p_virt_i2c->sda_gpio_pin, 1);
}

/**
 * @brief 
 * 
 * @param ack 读取完一个字节后是否发送一个应答信号
 */
uint8_t ft_virt_i2c_read_byte(ft_virt_i2c_t *p_virt_i2c, bool ack)
{
    uint8_t i = 0,recv_byte = 0;
    uint8_t sda_value = 0;

    conf_gpio_input(p_virt_i2c->sda_port_periph_clk, p_virt_i2c->p_sda_gpio_port, p_virt_i2c->sda_gpio_pin, GPIO_PuPd_UP);

    for(i = 0; i < 8; i++)
    {
        recv_byte <<= 1;

        set_gpio_value(p_virt_i2c->p_scl_gpio_port, p_virt_i2c->scl_gpio_pin, 0);
        ft_i2c_delay();
        set_gpio_value(p_virt_i2c->p_scl_gpio_port, p_virt_i2c->scl_gpio_pin, 1);

        get_gpio_value(p_virt_i2c->p_sda_gpio_port, p_virt_i2c->sda_gpio_pin, &sda_value);
        if(sda_value)
        {
            recv_byte++;
        }
        ft_i2c_delay();
    }

    if(ack)
    {
        ft_virt_i2c_set_ack(p_virt_i2c);
    }
    else
    {
        ft_virt_i2c_set_nack(p_virt_i2c);
    }

    return recv_byte;
}

