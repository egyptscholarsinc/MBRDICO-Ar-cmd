/*
 * File:    dictionary.hpp
 * Purpose: general purpose dictionary ( string key, string value )
 * Author: Vincent Pagel ( pagel@tcts.fpms.ac.be )
 * Version : 0.99
 * Time-stamp: <1999-01-22 11:31:01 pagel>
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

#ifndef DICTIONNARY_H
#define DICTIONNARY_H

#include <map>
#include <string>
using namespace std;
#include "LPhonemePlus.hpp"

class Dictionary: map<string, string, less<string> > 
{
public:
  Dictionary(istream& dico);
  bool search(const string& word, string& strresult) const;
  bool search(const string& word, LPhonemePlus& lppresult) const;
};
#endif
