#ifndef __LCD_DISPLAY_HANDLER_H
#define __LCD_DISPLAY_HANDLER_H


/**
 * LCD 上可显示的数码管
 */
typedef enum
{
    DIGITAL_1,
    DIGITAL_2,
    DIGITAL_3,
    DIGITAL_4,
    DIGITAL_5,
    DIGITAL_6,
    
    DIGITAL_T1,
    DIGITAL_T2,
    DIGITAL_T3,
    DIGITAL_T4,
    DIGITAL_T5,
    DIGITAL_T6,
    DIGITAL_T7,
    DIGITAL_T8,
    DIGITAL_T9,
    DIGITAL_T10,
    DIGITAL_T11,
    DIGITAL_T12,
    DIGITAL_T13,
} lcd_part_e;


typedef struct
{
    ht162x_t        ht162x;
    gpio_object_t   lcd_back_light_pin;
} lcd_display_obj_t;

int lcd_hw_init(void);
int lcd_display_init(void);
void lcd_display_loop_task(void);

void lcd_black_light_enable(bool enable);

#endif
