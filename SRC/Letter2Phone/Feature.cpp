/*
 * File:    feature.cpp
 * Purpose: feature in a decision tree (use a reference in a dictionary)
 * Author:  Vincent Pagel ( pagel@tcts.fpms.ac.be )
 * Version : 0.99
 * Time-stamp: <1998-11-19 12:35:23 pagel>
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

#include "Feature.hpp"

// *** STATIC MEMBER ***
// maintain a list of available codes
set<string, less<string> > Feature::aux_set;

Feature::Feature(const string& feat)
{
  pair< set<string, less< string > >::iterator, bool > p;
  p = Feature::aux_set.insert( feat );
  code= p.first; // iterator on the inserted string
}
