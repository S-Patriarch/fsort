// cst.h -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Заголовочный файл с определением констант.
 */

#pragma once
#if !defined(_CST_H)
#define _CST_H

#if !defined(_PTL_PTYPE_H)
#ifdef _WIN32
#include "ptl\ptype.h"
#else
#include "ptl/ptype.h"
#endif
#endif

constexpr ptl::__u32
_Part_Size { 500000 }; 

constexpr ptl::__u64
_Rand_Array_Size { 400000000 }; 

#endif // _CST_H