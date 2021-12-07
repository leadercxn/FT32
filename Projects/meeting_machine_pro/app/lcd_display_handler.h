#ifndef __LCD_DISPLAY_HANDLER_H
#define __LCD_DISPLAY_HANDLER_H

typedef struct
{
    ht162x_t        ht162x;
    gpio_object_t   lcd_ctrl_pin;
    gpio_object_t   lcd_back_light_pin;
} lcd_display_obj_t;

typedef enum
{
    SCREEN_L,
    SCREEN_R,
} screen_lr_e;

int lcd_display_init(void);
void lcd_display_loop_task(void);

uint16_t channel_index_lr_get(screen_lr_e lr);
uint16_t channel_freq_lr_get(screen_lr_e lr);
void channel_index_lr_set(screen_lr_e lr, uint16_t index);
void channel_freq_lr_set(screen_lr_e lr, uint16_t freq);
void channel_af_level_lr_set(screen_lr_e lr, uint8_t level);
void channel_rf_level_lr_set(screen_lr_e lr, uint8_t level);
void lcd_black_light_enable(bool enable);

#endif
