#include "board_config.h"
#include "mid_gpio.h"


int gpio_config(gpio_object_t *p_gpio_object)
{
    if(!p_gpio_object)
    {
        return -EINVAL;
    }

    int err_code = 0;

    if(p_gpio_object->gpio_dir == GPIO_DIR_OUTPUR)
    {
#ifdef FT32
        conf_gpio_output(p_gpio_object->gpio_port_periph_clk, p_gpio_object->p_gpio_port, p_gpio_object->gpio_pin);
#endif
    }
    else
    {
#ifdef FT32
        conf_gpio_input(p_gpio_object->gpio_port_periph_clk, p_gpio_object->p_gpio_port, p_gpio_object->gpio_pin, GPIO_PuPd_UP);
#endif
    }

    return err_code;
}

int gpio_output_set(gpio_object_t *p_gpio_object, uint8_t value)
{
    if(!p_gpio_object)
    {
        return -EINVAL;
    }

    int err_code = 0;

#ifdef FT32
    set_gpio_value(p_gpio_object->p_gpio_port, p_gpio_object->gpio_pin, value);
#endif

    return err_code;
}

int gpio_input_get(gpio_object_t *p_gpio_object, uint8_t *p_value)
{
    if(!p_gpio_object)
    {
        return -EINVAL;
    }

    int err_code = 0;

#ifdef FT32
    get_gpio_value(p_gpio_object->p_gpio_port, p_gpio_object->gpio_pin, p_value);
#endif

    return err_code;
}
