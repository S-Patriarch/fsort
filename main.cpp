// main.cpp -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 */

#include "cst.h"

#if !defined(_PTL_PTYPE_H)
#ifdef _WIN32
#include "ptl\ptype.h"
#else
#include "ptl/ptype.h"
#endif
#endif

#if !defined(_PTL_PCONIO_H)
#ifdef _WIN32
#include "ptl\pconio.h"
#else
#include "ptl/pconio.h"
#endif
#endif

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <ctime>
#include <chrono>

auto
write_data(const std::string&) -> void;

/*
 * Точка входа...
 */ 
auto
main() -> int
{
  ptl::setlocale_WIN32_rus();

  std::string __filename{ "data.txt" };

// ---
auto __start{ chrono::high_resolution_clock::now() };
// ---
  ::write_data(__filename);
  std::cout
    << "Генерация данных завершена."
    << std::endl;
// ---
auto __finish{ chrono::high_resolution_clock::now() };
// ---

  fstream _result;
  _result.open("result.txt", fstream::out | ofstream::trunc);
  _result.close();

  //auto __start{ chrono::high_resolution_clock::now() };

  //::sort(__filename);

  //auto __finish{ chrono::high_resolution_clock::now() };

  chrono::duration<double> elapsed = __finish - __start;

  std::cout
    << "Затраченное время: "
    << elapsed.count()
    << " секунд"
    << std::endl;

  return 0;
}

auto
write_data(const std::string& __filename) -> void
{
  fstream _fs;

  srand(time(nullptr));
  ptl::__s32 __left_border{ -100 };
  ptl::__s32 __range_len{ 50000 };

  _fs.open(__filename, fstream::out | ofstream::trunc);

  if (_fs.is_open())
    {
      for (ptl::__u64 __i{0}; __i < _Rand_Array_Sise; __i++)
        _fs 
          << (__left_border + rand() % __range_len)
          << ' ';
      _fs.close();
    }
}
