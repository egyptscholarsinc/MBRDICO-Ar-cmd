/*
 * File:    vp_error.cpp
 * Purpose: Error handling
 * Authors: V. Pagel and A. Ruelle  Email :  mbrola@tcts.fpms.ac.be
 * Version : 0.99
 * Time-stamp: <1999-06-24 14:12:32 pagel>
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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * History:
 *
 * 9/6/97: Created
 */
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "VpError.hpp"

#ifdef _MSC_VER
  #include "stdafx.h"
#endif

char errbuffer[200];				  // char buffer cumulating error messages
int lasterr_code=0;				  // Code of the last error

void fatal_message(const int code, const char *format, /* args */ ...)
{
  va_list ap;
  
  va_start(ap,format);
  lasterr_code=code;
  
#ifdef _MSC_VER
  vsprintf(errbuffer, format, ap);
  va_end(ap);
  AfxMessageBox(CString(errbuffer));  
#else
  vfprintf(stderr, format, ap);
  va_end(ap);
#endif 
  throw(code);
}

void warning_message(const int code, const char *format, /* args */ ...)
{
  va_list ap;
  
  va_start(ap,format);
  lasterr_code=code;
  
#ifdef _MSC_VER
  vsprintf(errbuffer, format, ap);
  va_end(ap);
  AfxMessageBox(CString(errbuffer));  
#else
  vfprintf(stderr, format, ap);
  va_end(ap);
#endif 
}
