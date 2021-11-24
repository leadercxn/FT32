#ifndef __MID_GPIO_H
#define __MID_GPIO_H

typedef enum
{
    GPIO_DIR_OUTPUR,
    GPIO_DIR_INPUT,
} gpio_dir_e;

typedef struct
{
#ifdef FT32
    uint32_t        gpio_port_periph_clk;
    GPIO_TypeDef    *p_gpio_port;
#endif
    uint32_t    gpio_pin;
    gpio_dir_e  gpio_dir;
    uint32_t    flag;
} gpio_object_t;

int gpio_config(gpio_object_t *p_gpio_object);

int gpio_output_set(gpio_object_t *p_gpio_object, uint8_t value);

int gpio_input_get(gpio_object_t *p_gpio_object, uint8_t *p_value);
#endif
