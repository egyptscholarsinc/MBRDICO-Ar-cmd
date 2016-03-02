/*
 * File:    letter2phoneLR.h
 * Purpose: transcribe a word, from a decision tree (right to left)
 * Author:  Vincent Pagel ( pagel@tcts.fpms.ac.be )
 * Version : 0.99
 * Time-stamp: <1999-06-24 17:12:28 pagel>
 * 
 * Copyright (c) 1999 Faculte Polytechnique de Mons (TCTS lab)
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
 * 21/06/99: Created
 */

#ifndef LETTER2PHONELR_H
#define LETTER2PHONELR_H

#include "Letter2Phone.hpp"

class Letter2PhoneLR: public Letter2Phone 
{
 public:
  // Default constructor
  Letter2PhoneLR(istream& st, int ns, int lg, int rg, int nf):Letter2Phone(st, ns, lg, rg, nf)
	 {}
  
  // redefine trancription function
  void transcribe(LPhonemePlus& lpp, const string& target, const string * tags) const;
};

#endif
