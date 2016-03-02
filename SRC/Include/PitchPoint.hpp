/*
 * File:    PitchPoint.hpp
 * Purpose: pair of percentage/f0 in hertz
 * Author: Vincent Pagel ( pagel@tcts.fpms.ac.be )
 * Version : 0.99
 * Time-stamp: <1999-06-24 14:14:26 pagel>
 * 
 * Copyright (c) 1998-1999 Faculte Polytechnique de Mons (TCTS lab)
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

#ifndef PITCHPOINT_H
#define PITCHPOINT_H

# include <iostream>
using namespace std;

class PitchPoint
{
public:
  PitchPoint(); // to please Visual STL
  PitchPoint(double npos, double nfreq); // position in percentage and freq in Hertz
  double get_pos() const { return pos; }
  double get_freq() const { return freq; }
  void set(const double& npos,const double& nfreq) { pos=npos; freq=nfreq; }

  // To please STL lists... but not implemented
  bool operator<(const PitchPoint& b) const;
  bool operator>(const PitchPoint& b) const;
  bool operator==(const PitchPoint& b) const;
  bool operator!=(const PitchPoint& b) const;
  
protected:
  double pos;
  double freq;
};

// Output in .pho format
ostream& operator<<( ostream& o, const PitchPoint& p);

#endif
