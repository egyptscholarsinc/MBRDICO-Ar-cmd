/*
 * File:    VpError.hpp
 * Purpose: little usefull functions to manage error
 * Author: V. Pagel ( pagel@tcts.fpms.ac.be )
 * Version : 0.99
 * Time-stamp: <1999-02-01 13:34:07 pagel>
 * 
 * Copyright (c) 1998 Faculte Polytechnique de Mons (TCTS lab)
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation version 1
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * 10/06/96 : Created by VP. Put here all little usefull functions to manage
 * errors, depending on the mode: LIBRARY, or CONSOLE (means stderr output
 * or buffering of the messages)
 */

#ifndef VP_ERROR_H
#define VP_ERROR_H

#include <stdio.h>
#include <stdarg.h>

/*
 * For the DLL and LIBRARY mode, Error codes returned
 */
#define ERROR_UNKNOWNCOMMAND -10

extern char errbuffer[200];			  // char buffer cumulating error messages
extern int lasterr_code;				  // Code of the last error

void fatal_message(const int code, const char *format, /* args */ ...);
void warning_message(const int code, const char *format, /* args */ ...);

inline void debug_message(char const *format, /* args */ ...)
{	
  //  If we're not debugging, the macro is empty -> no code generated
  // this is the reason for the inline ....
#ifdef DEBUG
  va_list ap;
  
  va_start(ap,format);
  
#ifdef LIBRARY
  vsprintf(errbuffer, format, ap);
  va_end(ap);
#else
  vfprintf(stderr, format, ap);
  va_end(ap);
#endif 
#endif
}

#ifdef DEBUG
#   define debug(X)  X
#else
#   define debug(X)
#endif

#endif
