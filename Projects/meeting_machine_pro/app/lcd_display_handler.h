#ifndef __LCD_DISPLAY_HANDLER_H
#define __LCD_DISPLAY_HANDLER_H

#define SCREEN_R_CHANNEL_INDEX_MAX  200
#define SCREEN_R_CHANNEL_INDEX_MIN  101

#define SCREEN_R_CHANNEL_FREQ_MIN   6600

#define SCREEN_L_CHANNEL_INDEX_MAX  100
#define SCREEN_L_CHANNEL_INDEX_MIN  1

#define SCREEN_L_CHANNEL_FREQ_MIN   6320

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
    DIGITAL_7,
    DIGITAL_8,
    DIGITAL_9,
    DIGITAL_10,
    DIGITAL_11,
    DIGITAL_12,
    DIGITAL_13,
    DIGITAL_14,
    DIGITAL_15,
    DIGITAL_16,
    DIGITAL_S3,
    DIGITAL_S4,

    DIGITAL_S1,
    DIGITAL_S2,

    DIGITAL_T1,
    DIGITAL_T2,
    DIGITAL_T3,
    DIGITAL_T4,
    DIGITAL_T5,

    DIGITAL_X1,
    DIGITAL_X2,
    DIGITAL_X3,
    DIGITAL_X4,
    DIGITAL_X5,

    DIGITAL_M1,
    DIGITAL_M2,
    DIGITAL_M3,
    DIGITAL_M4,
    DIGITAL_M5,

    DIGITAL_W1,
    DIGITAL_W2,
    DIGITAL_W3,
    DIGITAL_W4,
    DIGITAL_W5,
} lcd_part_e;

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

typedef enum
{
    EXIT_SET_MODE,
    L_SETTING_MODE,
    R_SETTING_MODE,
} lcd_settings_mode_e;

int lcd_hw_init(void);
int lcd_display_init(void);
void lcd_display_loop_task(void);

uint16_t channel_index_lr_get(screen_lr_e lr);
void channel_index_lr_set(screen_lr_e lr, uint16_t index);
void channel_af_level_lr_set(screen_lr_e lr, uint8_t level);
void channel_rf_level_lr_set(screen_lr_e lr, uint8_t level);
void lcd_black_light_enable(bool enable);
void lcd_ctrl_enable(bool enable);

lcd_settings_mode_e channel_settings_mode_get(void);
void channel_settings_mode_set(lcd_settings_mode_e mode);
bool lcd_off_status_get(void);
void lcd_off_status_set(bool enable);

#endif
