/*
 * File:    LPitchPoint.cpp
 * Purpose: List of pitch points, ie pairs( percent / f0 in hertz )
 * Author:  Vincent Pagel ( pagel@tcts.fpms.ac.be )
 * Version : 0.99
 * Time-stamp: <1999-01-20 17:17:30 pagel>
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
 *  10/03/98 : Created
 */

#include "LPitchPoint.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;

// Output in .pho format
ostream&
operator<< (ostream& o, const LPitchPoint& lp)
{
  copy(lp.begin(),lp.end(),ostream_iterator<PitchPoint>(o," "));
  return o;
}
