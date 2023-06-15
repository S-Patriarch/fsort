// main.cpp -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 */

#include "cst.h"

#if !defined(_PTL_PALGORITHM_H)
#ifdef _WIN32
#include "ptl\palgorithm.h"
#else
#include "ptl/palgorithm.h"
#endif
#endif

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <chrono>
#include <experimental/filesystem>

#ifdef _WIN32
#include <clocale>
#endif

auto write_data(const std::string&) -> void;
auto read_part_array(std::fstream&, int*&) -> int;
auto partition(int*&, int, int) -> int;
auto quick_sort(int*&, int, int) -> void;
auto merge_to_file(const int*, const int*, int, int) -> void;
auto merge_file() -> void;
auto sort(const std::string&) -> void;

/*
 * Точка входа...
 */ 
auto
main() -> int
{
  #ifdef _WIN32
   setlocale( LC_ALL, "Russian" );
  #endif

  std::string  __filename{ "data.txt" };

  ::write_data(__filename);
  std::cout
    << "Генерация данных завершена."
    << std::endl;

  std::fstream _result;
  _result.open("result.txt", std::fstream::out | std::ofstream::trunc);
  _result.close();

  auto __start{ std::chrono::high_resolution_clock::now() };
  ::sort(__filename);
  auto __finish{ std::chrono::high_resolution_clock::now() };

  std::chrono::duration<double> elapsed = __finish - __start;

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
  std::fstream _fs;

  srand(time(nullptr));

  int  __left_border{ -100 };
  int  __range_len{ 50000 };

  _fs.open(__filename, std::fstream::out | std::ofstream::trunc);

  if (_fs.is_open())
    {
      std::cout
        << "Генерация данных... "
        << std::endl;

      for (int __i{0}; __i < _Rand_Array_Size; __i++)
        {
          _fs 
            << (__left_border + rand() % __range_len)
            << ' ';
        }

      std::cout << std::endl;
      _fs.close();
    }
}

auto
read_part_array(std::fstream& _fs, int*&  __array) -> int
{
  __array = new int[_Part_Size];

  int*  __temp_array{ nullptr };
  int   __i{}; 

  for (__i = 0; __i < _Part_Size && !_fs.eof(); __i++)
    _fs >> __array[__i];

  if (__i == 1)
    {
      delete[] __array;
      return 0;
    }

  if (__i != _Part_Size)
    {
      __temp_array = new int[__i];

      for (int __j{0}; __j < __i; __j++)
        __temp_array[__j] = __array[__j];

      delete[] __array;
      __array = __temp_array;

      return (__i - 1);
    }

  return _Part_Size;
}

auto
partition(int*& __array, int __low, int __high) -> int
{
  int  __pivot{ __array[__high] };
  int  __i{ __low - 1 };

  for (int __j{__low}; __j <= __high-1; __j++)
    {
      if (__array[__j] <= __pivot)
        {
          __i++;
          ptl::swap(__array[__i], __array[__j]);
        }
    }

  ptl::swap(__array[__i+1], __array[__high]);
  return (__i + 1);
}

auto
quick_sort(int*& __array, int __low, int __high) -> void
{
  if (__low < __high)
    {
      int  __pi{ ::partition(__array, __low, __high) };

      ::quick_sort(__array, __low, __pi - 1);
      ::quick_sort(__array, __pi + 1, __high);
    }
}

auto
merge_to_file(const int* __array_1,
              const int* __array_2,
              int        __size_1,
              int        __size_2) -> void
{
  std::fstream _temp;

  const int*  __first{ nullptr };
  const int*  __second{ nullptr };

  _temp.open("temp_1.txt", std::fstream::out | std::ofstream::trunc);

  if (__array_1[0] < __array_2[0])
    {
      __first  = __array_1;
      __second = __array_2;
    }
  else 
    {
      __first  = __array_2;
      __second = __array_1;
      ptl::swap(__size_1, __size_2);
    }

  if (_temp.is_open())
    {
      int  __i{ };
      int  __j{ };

      while (__i < __size_1 && __j < __size_2)
        {
          if (__first[__i] < __second[__j])
            _temp
              << __first[__i++]
              << ' ';
          else if (__first[__i]  == __second[__j])
            {
              _temp
                << __first[__i++]
                << ' ';
              _temp
                << __second[__j++]
                << ' ';
            }
          else
              _temp
                << __second[__j++]
                << ' ';
        }

      while (__i < __size_1)
        _temp
          << __first[__i++]
          << ' ';

      while (__i < __size_2)
        _temp
          << __second[__j++]
          << ' ';

      _temp.close();
    }
}

auto
merge_file() -> void
{
  std::fstream _res;
  std::fstream _temp_1;
  std::fstream _temp_2;

  _temp_1.open("temp_1.txt", std::fstream::in);
  _res.open("result.txt", std::fstream::in);
  _temp_2.open("temp_2.txt", std::fstream::out | std::ofstream::trunc);

  if (!_temp_1.is_open() || !_temp_2.is_open() || !_res.is_open())
    return;

  int  __temp_1_value{ };
  int  __res_value{ };

  _temp_1 >> __temp_1_value;
  _res    >> __res_value;

  while (!_temp_1.eof() && !_res.eof())
    {
      if (__temp_1_value <= __res_value)
        {
          _temp_2 
            << __temp_1_value 
            << ' ';
          _temp_1
            >> __temp_1_value;
        }
      else
        {
          _temp_2
            << __res_value
            << ' ';
          _res 
            >> __res_value;
        }
    }

  while (!_res.eof())
    {
      _temp_2
        << __res_value
        << ' ';
      _res 
        >> __res_value;
    }

  while (!_temp_1.eof())
    {
      _temp_2
        << __temp_1_value
        << ' ';
      _temp_1
        >> __temp_1_value;
    }

  _temp_1.close();
  _temp_2.close();
  _res.close();

  _res.open("result.txt", std::fstream::out | std::ofstream::trunc);
  if (_res.is_open())
    _res.close();

  if (!std::filesystem::copy_file("temp_2.txt", "result.txt", 
      std::filesystem::copy_options::overwrite_existting))
    return;
/*
  std::ifstream _scr( "temp_2.txt", std::ios::binary );
  std::ifstream _dst( "result.txt", std::ios::binary );
  _dst << _scr.rdbuf();
*/
}

auto
sort(const std::string& __filename) -> void
{
  std::fstream _fs;
  _fs.open(__filename, std::fstream::in);

  if (_fs.is_open()) 
    {
      while (!_fs.eof())
        {
          int*  __part_1{ nullptr };
          int*  __part_2{ nullptr };

          int   __size_1{ ::read_part_array(_fs, __part_1) };
          int   __size_2{ ::read_part_array(_fs, __part_2) };

          if (__size_1 == 0 || __size_2 == 0)
            return;

          std::cout
            << " size_1 = " << __size_1
            << " size_2 = " << __size_2
            << std::endl;

          ::quick_sort(__part_1, 0, __size_1 - 1);
          ::quick_sort(__part_2, 0, __size_2 - 1);

          ::merge_to_file(__part_1, __part_2, __size_1, __size_2);
          ::merge_file();
        }

      _fs.close();
    }
}