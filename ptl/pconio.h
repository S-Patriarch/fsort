// -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Описание библиотеки для работы с консолью (терминалом).
 */

/**
 *  (PTL) Patriarch library : pconio.h
 */

#pragma once
#if !defined(_PTL_PCONIO_H)
#define _PTL_PCONIO_H

#if !defined(_PTL_PTYPE_H)
#include "ptype.h"
#endif

#include <iostream>
#include <termios.h>
#include <stdio.h>

#ifdef _WIN32
#include <clocale>
#include <windows.h>
#endif

/*
 * Функции:
 *   - setlocale_WIN32_rus() - локализация консоли ОС Windows для вывода
 *   - setconsole_WIN32_rus() - локализация консоли ОС Windows для ввода/вывода
 *   - clrscr() - очистка терминала
 *   - clreol() - удаляет все символы после курсора до конца строки
 *   - gotoxy() - постановка курсора в координаты __x и __y терминала
 *   - where_x() - возвращает установленную координату __text._S_cur_x
 *   - where_y() - возвращает установленную координату __text._S_cur_y
 *   - getche() - ввод одного символа с отображением этого символа
 *   - getch() - ввод одного символа без отображения этого символа
 */

namespace ptl
{
  struct textinfo
  {
    __u16  _S_cur_x{ 0 };
    __u16  _S_cur_y{ 0 };
  } __text;

  /* 
   * Локализация консоли ОС Windows для вывода
   * текста на русском языке.
   */ 
  auto
  setlocale_WIN32_rus() -> void
  {
    #ifdef _WIN32
      setlocale(LC_ALL, "Russian");
    #endif
  }

  /* 
   * Локализация консоли ОС Windows для ввода/вывода
   * текста на русском языке.
   */ 
  auto
  setconsole_WIN32_rus() -> void
  {
    #ifdef _WIN32
      SetConsoleCP(1251);
      SetConsoleOutputCP(1251);
    #endif
  }

  /* 
   * Очистка терминала и постановка курсора в 
   * верхний левый угол.
   */
  auto
  clrscr() -> void
  { std::cout << "\033[2J\033[1;1H"; }

  /* 
   * Удаляет все символы, находящиеся после курсора и до конца
   * строки, но не удаляет символы, расположенные перед
   * текущей позицией курсора.
   */
  auto
  clreol() -> void
  { std::cout << "\033[K"; }

  /* 
   * Постановка курсора в координаты __x и __y терминала.
   */ 
  auto
  gotoxy(__u16 __x, __u16 __y) -> void
  { 
    std::cout 
      << "\033[" 
      << __y 
      << ";" 
      << __x 
      << "H";

    __text._S_cur_x = __x;
    __text._S_cur_y = __y;
  }

  /* 
   * Возвращает установленную координату __text._S_cur_x.
   */ 
  auto
  where_x() -> __u16
  { return __text._S_cur_x; }

  /* 
   * Возвращает установленную координату __text._S_cur_y.
   */ 
  auto
  where_y() -> __u16
  { return __text._S_cur_y; }

  /* 
   * Получает пользовательский ввод в форме одного символа с 
   * отображением этого символа на экране и без необходимости 
   * нажимать клавишу 'Enter'.
   */ 
  auto
  getche() -> __u16
  {
    struct termios __t;
    __u16          __c;

    tcgetattr(0, &__t);
    __t.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &__t);
    fflush(stdout);
    __c = getchar();
    __t.c_lflag |= ICANON;
    tcsetattr(0, TCSANOW, &__t);

    return __c;
  }

  /* 
   * Получает пользовательский ввод в форме одного символа без 
   * отображения этого символа на экране и без необходимости 
   * нажимать клавишу 'Enter'.
   */ 
  auto
  getch() -> __u16
  {
    struct termios __t;
    __u16          __c;

    tcgetattr(0, &__t);
    __t.c_lflag &= ~ECHO + ~ICANON;
    tcsetattr(0, TCSANOW, &__t);
    fflush(stdout);
    __c = getchar();
    __t.c_lflag |= ICANON + ECHO;
    tcsetattr(0, TCSANOW, &__t);

    return __c;
  }

} // namespace ptl

#endif // _PTL_PCONIO_H