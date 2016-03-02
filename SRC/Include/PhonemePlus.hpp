/*
 * File:    PhonemePlus.hpp
 * Purpose: a Phoneme, its duration, its pitchpoints, and its prosodic markers
 * Author: Vincent Pagel ( pagel@tcts.fpms.ac.be )
 * Version : 0.99
 * Time-stamp: <1999-06-24 14:14:05 pagel>
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

#ifndef PHONEMEPLUS_H
#define PHONEMEPLUS_H

# include <iostream>
# include <fstream>
using namespace std;

#include <string>
#include "Phoneme.hpp"
#include "LPitchPoint.hpp"

class PhonemePlus
{
public:
  PhonemePlus() {};
  PhonemePlus(const string& phoneme);

  const Phoneme& get_phone() const { return phone; }

  double get_duration() const { return duration; }
  void set_duration(double nduration) { duration=nduration;}

  const string& get_prosody()  const { return prosody; }
  void append_prosody(const string& str) { prosody += str; }

  const LPitchPoint& get_pitch() const { return pitch; }
  void append_pitch(const PitchPoint& pp) { pitch.push_back(pp); }

  void erase();

  // To please the stl list
  bool operator== (const PhonemePlus& p) const;
  bool operator< (const PhonemePlus& p) const;
  bool operator> (const PhonemePlus& p) const;
  bool operator!= (const PhonemePlus& p) const;

  friend ifstream& in_phofile(ifstream& o, PhonemePlus &p);

protected:
  Phoneme phone;      // the phoneme
  double duration;    // duration in milliseconds
  LPitchPoint pitch;  // pitch curve
  string prosody;     // tones and accent
};

// Output in .pho format
ostream& operator<< (ostream& o, const PhonemePlus& p);

#endif
