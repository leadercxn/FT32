/* Copyright (c) 2020 SENSORO Co.,Ltd. All Rights Reserved.
 *
 */

#ifndef BOARDS_H__
#define BOARDS_H__

#if defined(BOARD_DEMO)
#include "board_demo.h"
#elif defined(BOARD_SWC11XS)
#include "board_swc11xs.h"
#else
#error "board is not defined"
#endif

#endif
