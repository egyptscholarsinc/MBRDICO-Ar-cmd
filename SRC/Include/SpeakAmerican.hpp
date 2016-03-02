/*
 * File:    SpeakAmerican.hpp
 * Purpose: phonetize and sprinkles with prosodic markers (American heir)
 * Author: Vincent Pagel ( pagel@tcts.fpms.ac.be ) 
 * Version : 0.99
 * Time-stamp: <1999-06-23 12:33:25 pagel>
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

#ifndef SPEAKAMERICAN_H
#define SPEAKAMERICAN_H

#include <stdio.h>
#include "Speak.hpp"

class SpeakAmerican : public Speak
{
public:
  SpeakAmerican(istream& zscore,         // Phoneme Durations
					 istream& exception,      // exception for letter2phoneme
					 istream& decision,       // decision tree for letter2phoneme
					 const char* mbrola_dba); // mbrola databases

  // Redefined
  virtual double thonification(LPhonemePlus& lpp) const;
  virtual void  prosodification(LPhonemePlus& lpp,
										  double init_f0, double ambitus, double speed) const; 
};

#endif
