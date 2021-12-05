#ifndef __LCD_DISPLAY_HANDLER_H
#define __LCD_DISPLAY_HANDLER_H

typedef struct
{
    ht162x_t        ht162x;
    gpio_object_t   lcd_ctrl_pin;
    gpio_object_t   lcd_back_light_pin;
} lcd_display_obj_t;


void lcd_display_init(void);

#endif
