// -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Описание библиотеки для псевдонимов предопределенных типов данных.
 */

/**
 *  (PTL) Patriarch library : ptype.h
 */

#pragma once
#if !defined(_PTL_PTYPE_H)
#define _PTL_PTYPE_H

/*
 * __s16 - 32 767
 * __u16 - 65 535
 *
 * __s32 - 2.14748e+09
 * __u32 - 4.29497e+09
 *
 * __s64 - 9.22337e+18
 * __u64 - 1.84467e+19
 */

namespace ptl
{
  typedef signed short int       __s16;
  typedef unsigned short int     __u16;

  typedef signed int             __s32;
  typedef unsigned int           __u32;

  typedef signed long long int   __s64;
  typedef unsigned long long int __u64;

} // namespace ptl

#endif // _PTL_PTYPE_H