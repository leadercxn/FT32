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

#define Digital_1 0x00 //数码管1
#define Digital_2 0x01 //数码管2
#define Digital_3 0x02 //数码管3

#define DigitalSeg3_L 0x00 //数码管3 seg1
#define DigitalSeg3_H 0x01 //数码管3 seg2

#define DigitalSeg2_L 0x02 //数码管3 seg3
#define DigitalSeg2_H 0x03 //数码管3 seg4

#define DigitalSeg1_L 0x04 //数码管3 seg5
#define DigitalSeg1_H 0x05 //数码管3 seg6

#define Digital_4 0x00 //数码管4
#define Digital_5 0x01 //数码管5
#define Digital_6 0x02 //数码管6

#define DigitalSeg4_L 0x1E //数码管4 seg31
#define DigitalSeg4_H 0x1F //数码管4 seg32

#define DigitalSeg5_L 0x1C //数码管5 seg29
#define DigitalSeg5_H 0x1D //数码管5 seg30

#define DigitalSeg6_L 0x1A //数码管6 seg27
#define DigitalSeg6_H 0x1B //数码管6 seg28

#define Digital_7 0x00  //数码管7
#define Digital_8 0x01  //数码管8
#define Digital_9 0x02  //数码管9
#define Digital_10 0x03 //数码管10
#define Digital_11 0x04 //数码管11
#define Digital_S3 0x05 //数码管S3
#define Digital_12 0x06 //数码管12
#define Digital_13 0x07 //数码管13
#define Digital_14 0x08 //数码管14
#define Digital_15 0x09 //数码管15
#define Digital_16 0x0A //数码管16
#define Digital_S4 0x0B //数码管S4

#define DigitalSeg7_L 0x08 //数码管7 seg9
#define DigitalSeg7_H 0x09 //数码管7 seg10
#define DigitalSeg8_L 0x0A //数码管8 seg11
#define DigitalSeg8_H 0x0B //数码管8 seg12
#define DigitalSeg9_L 0x0C //数码管9 seg13
#define DigitalSeg9_H 0x0D //数码管9 seg14

#define DigitalSeg10_L 0x0E //数码管10 seg15
#define DigitalSeg10_H 0x0F //数码管10 seg16

#define DigitalSeg12_L 0x10 //数码管12 seg17
#define DigitalSeg12_H 0x11 //数码管12 seg18

#define DigitalSeg13_L 0x12 //数码管13 seg19
#define DigitalSeg13_H 0x13 //数码管13 seg20

#define DigitalSeg14_L 0x14 //数码管14 seg21
#define DigitalSeg14_H 0x15 //数码管14 seg22

#define DigitalSeg15_L 0x16 //数码管15 seg23
#define DigitalSeg15_H 0x17 //数码管15 seg24

/**@brief Structure encode dev_status
 */
typedef struct
{
    //---- 段显示   -gfe dcba
    uint8_t seg_a; //BIT:0
    uint8_t seg_b; //BIT:1
    uint8_t seg_c; //BIT:2
    uint8_t seg_d; //BIT:3
    uint8_t seg_e; //BIT:4
    uint8_t seg_f; //BIT:5
    uint8_t seg_g; //BIT:6
    uint8_t seg_x; //BIT:7
} __attribute__((__packed__)) encode_seg_code_t;

typedef struct
{
    uint8_t com1;
    uint8_t com2;
    uint8_t com3;
    uint8_t com4;
} seg_com_t;

typedef struct
{
    uint8_t high; //高位
    uint8_t mid;  //中间位
    uint8_t low;  //低位
} seg_data_t;

void digital_to_segdata(encode_seg_code_t *seg_code, uint8_t digital);
void segdata_to_segcom_mode_0(encode_seg_code_t seg_code, uint8_t *com_data_h, uint8_t *com_data_l);
void segdata_to_segcom_mode_1(encode_seg_code_t seg_code, uint8_t *com_data_h, uint8_t *com_data_l);
void segdata_to_segcom_mode_2(encode_seg_code_t seg_code, uint8_t *com_data_h, uint8_t *com_data_l);
void segdata_convertor(uint32_t value, seg_data_t *seg_data);
#endif
