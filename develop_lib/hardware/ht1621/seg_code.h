/* Copyright (c) 2019 SENSORO Co.,Ltd. All Rights Reserved.
 *
 */

#ifndef __SEG_CODE_H__
#define __SEG_CODE_H__

#define BIT_0 0x01 /**< The value of bit 0 */
#define BIT_1 0x02 /**< The value of bit 1 */
#define BIT_2 0x04 /**< The value of bit 2 */
#define BIT_3 0x08 /**< The value of bit 3 */
#define BIT_4 0x10 /**< The value of bit 4 */
#define BIT_5 0x20 /**< The value of bit 5 */
#define BIT_6 0x40 /**< The value of bit 6 */
#define BIT_7 0x80 /**< The value of bit 7 */

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


/**@brief Structure encode dev_status
 */
typedef struct
{
    //---- 段显示   -gfe dcba
    uint8_t seg_a :1; //BIT:0
    uint8_t seg_b :1; //BIT:1
    uint8_t seg_c :1; //BIT:2
    uint8_t seg_d :1; //BIT:3
    uint8_t seg_e :1; //BIT:4
    uint8_t seg_f :1; //BIT:5
    uint8_t seg_g :1; //BIT:6
    uint8_t seg_x :1; //BIT:7
} __attribute__((__packed__)) encode_seg_code_t;

typedef struct
{
    uint8_t high; //高位
    uint8_t mid;  //中间位
    uint8_t low;  //低位
} seg_data_t;

void digital_to_segdata(encode_seg_code_t *seg_code, uint8_t digital);
void segdata_convertor(uint32_t value, seg_data_t *seg_data);
#endif
