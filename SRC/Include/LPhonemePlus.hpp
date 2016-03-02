/*
 * File:    LPhonemePlus.hpp
 * Purpose: List of augmented phonemic representation ( equiv to .pho file)
 * Author:  Vincent Pagel ( pagel@tcts.fpms.ac.be )
 * Version : 0.99
 * Time-stamp: <1999-06-25 11:05:09 pagel>
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

#ifndef LPHONEMEPLUS_H
#define LPHONEMEPLUS_H

# include <iostream>
using namespace std;

#include <list>
#include "PhonemePlus.hpp"

class LPhonemePlus: public list<PhonemePlus>
{
public:
  LPhonemePlus():nb_insert(0) {}
  
  // Read a pho file coming from MBROLA
  void ReadPhofile(char *file_name);   

  // Read a pho line from a phonological transcription database
  // phoneme + accentuation
  void ReadPhonologic(const char* line);  

  // Same as ReadPhonologic but read from a stream
  bool ReadPhonologic(istream* is);     

  // Look for the first INSERT tag and replace it with the Lpp
  void insert_target(LPhonemePlus& lpp);

  // Look for the first INSERT tag and return its prosodic parameters
  bool LPhonemePlus::get_param_insert(double& init_f0, 
												  double& ambitus,
												  double& speed);
  
  // Number of insert spot remaining
  int get_nb_insert() const {return nb_insert;}

private:
  int nb_insert; // Number of insertion point in the phonemic string
};

// Output in .pho format
ostream& operator<< (ostream& o, const LPhonemePlus& p);

#endif
