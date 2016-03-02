/*
 * File:    LPitchPoint.hpp
 * Purpose: List of pitch points, ie pairs( percent / f0 in hertz )
 * Author:  Vincent Pagel ( pagel@tcts.fpms.ac.be )
 * Version : 0.99
 * Time-stamp: <1999-06-24 14:13:28 pagel>
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
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef LPITCHPOINT_H
#define LPITCHPOINT_H

# include <iostream>
using namespace std;

#include <list>
#include "PitchPoint.hpp"

class LPitchPoint: public list<PitchPoint>
{
};

// Output in .pho format
ostream& operator<< ( ostream& o, const LPitchPoint& lp);

#endif
