/*
 * File:    zphoneme.hpp
 * Purpose: Phoneme properties: zscores and voicing properties
 * Author: V. Pagel ( pagel@tcts.fpms.ac.be )
 * Version : 0.99
 * Time-stamp: <1999-01-22 11:27:21 pagel>
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
 */

#ifndef ZPHONEME_H
#define ZPHONEME_H

#include <map>
#include <string>
#include "Phoneme.hpp"
#include "PhonemePlus.hpp"

typedef pair<double,double> Zratio;
typedef string Flags;

typedef struct {
	Zratio zratio;
	Flags flags;
} ZPhone;

class ZPhoneme: map<Phoneme, ZPhone, less<Phoneme> > 
{
public:
  // same from a stream (read to the end of file)
  ZPhoneme(istream& zs);
  
  bool is_a(const Phoneme& ph,const char a_flag) const;
  bool is_a(const Phoneme& ph,const string& flags) const;
  const Zratio& ZPhoneme::zscore(const PhonemePlus& pp) const;
};

#endif
