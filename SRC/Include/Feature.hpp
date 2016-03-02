/*
 * File:    feature.hpp
 * Purpose: feature in a decision tree (implemented for a fast comparison between
 *          elements belonging to a small set of values)
 * Author:  Vincent Pagel ( pagel@tcts.fpms.ac.be )
 * Version : 0.99
 * Time-stamp: <1999-06-24 14:11:54 pagel>
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
 * 19/11/98: Created
 */

#ifndef FEATURE_H
#define FEATURE_H

#include <set>
#include <string>
using namespace std;

class Feature
{
public:
  Feature() {}
  Feature(const string& feat);
  
  const string& str() const { return *code; }
  
  // Compare the codes directly
  bool operator== (const Feature& f) const { return code == f.code; }
  bool operator!= (const Feature& f) const { return code != f.code; }
  bool operator< (const Feature& f) const; // to please Visual
  
protected:
  // *** STATIC MEMBER ***
  // maintain a list of available codes in associative set
  static set<string, less<string> > aux_set;
  
  // The actual code for a feature is a pointer on a frozen string
  // much faster for comparison and spares some storage
  set<string, less<string> >::iterator code; 
};

inline ostream& operator<< (ostream& o, const Feature& feat)
{ return o << feat.str(); }

#endif
