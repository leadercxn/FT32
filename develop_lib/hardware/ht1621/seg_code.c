/* Copyright (c) 2019 SENSORO Co.,Ltd. All Rights Reserved.
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include "seg_code.h"

#include "trace.h"

static uint8_t m_seg_code[16] = {
    //---- 段显示   -gfe dcba
    0x3F, //[0]    [0011 1111]
    0x06, //[1]    [0000 0110]
    0x5B, //[2]    [0101 1011]
    0x4F, //[3]    [0100 1111]
    0x66, //[4]    [0110 0110]
    0x6D, //[5]    [0110 1101]
    0x7D, //[6]    [0111 1101]
    0x07, //[7]    [0000 0111]
    0x7F, //[8]    [0111 1111]
    0x6F, //[9]    [0110 0111]
    0x77, //[A]    [0111 0111]
    0x7C, //[B]    [0111 1100]
    0x39, //[C]    [0011 1001]
    0x5E, //[D]    [0101 1110]
    0x79, //[E]    [0111 1001]
    0x71  //[F]    [0111 0001]
};

void digital_to_segdata(encode_seg_code_t *seg_code, uint8_t digital)
{
    uint8_t data = m_seg_code[digital];

    seg_code->seg_a = data & BIT_0 ? 1 : 0;
    seg_code->seg_b = data & BIT_1 ? 1 : 0;
    seg_code->seg_c = data & BIT_2 ? 1 : 0;
    seg_code->seg_d = data & BIT_3 ? 1 : 0;
    seg_code->seg_e = data & BIT_4 ? 1 : 0;
    seg_code->seg_f = data & BIT_5 ? 1 : 0;
    seg_code->seg_g = data & BIT_6 ? 1 : 0;
    seg_code->seg_x = 0;
    trace_verbose("data =0x%02x\r\n", data);
    trace_verbose("seg_code->xgfedcba=%d%d%d%d %d%d%d%d\r\n",
               seg_code->seg_x,
               seg_code->seg_g,
               seg_code->seg_f,
               seg_code->seg_e,
               seg_code->seg_d,
               seg_code->seg_c,
               seg_code->seg_b,
               seg_code->seg_a);
}

void segdata_convertor(uint32_t value, seg_data_t *seg_data)
{
    seg_data->high = (value % 1000) / 100;
    seg_data->mid = (value % 100) / 10;
    seg_data->low = value % 10;
    trace_verbose("seg_data->high =%d\r\n", seg_data->high);
    trace_verbose("seg_data->mid =%d\r\n", seg_data->mid);
    trace_verbose("seg_data->low =%d\r\n", seg_data->low);
}
