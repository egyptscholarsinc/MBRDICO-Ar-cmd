/*
 * File:    LPhonemePlus.cpp
 * Purpose: List of augmented phonemic representation ( equiv to .pho file)
 * Author:  Vincent Pagel ( pagel@tcts.fpms.ac.be )
 * Version : 0.99
 * Time-stamp: <1999-06-25 11:04:30 pagel>
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

#include <fstream>
#include "VpError.hpp"
#include "LPhonemePlus.hpp"

// Read a pho file coming from MBROLA
void
LPhonemePlus::ReadPhofile(char *file_name)
{
  PhonemePlus pp;
  ifstream is(file_name);
  
  while (in_phofile(is,pp))
	 {
		push_back(pp);
		if (pp.get_phone()==";;INSERT")
		  nb_insert++;
		pp.erase();
	 }
}

// Read a pho line from a phonological transcription database
// phoneme + accentuation
void
LPhonemePlus::ReadPhonologic(const char* line)
{
  // Scan a line like:
  // z e R o1
  size_t position=0;
  const char* rest=line;
  char phone_name[200];
		
  while(sscanf(rest," %s%n",phone_name,&position)==1)
	 {
		rest=&rest[position];
		push_back( PhonemePlus(phone_name) );
	 }
}

// Read a pho line from a phonological transcription database
// phoneme + accentuation space separated
bool
LPhonemePlus::ReadPhonologic(istream* is)
{
  char line[1024];

  // Scan a line like:
  // z e R o1
  if (is->getline(line,sizeof(line)))
	 {
		ReadPhonologic(line);
		return true;
	 }
  else
	  return false;
}

// Look for the first INSERT tag and replace it with the Lpp
void LPhonemePlus::insert_target(LPhonemePlus& lpp)
{
  // Search insertion point
  iterator i;
  for(i=begin(); i!=end(); i++)
	 {
		if ((*i).get_phone()==";;INSERT")
		  break;
	 }
  // Sanity check
  if (i==end())
	 {
		fatal_message(-1,"Reach end of carrier without target\n");
	 }
  // Insert, then remove the INSERT marker
  insert(i,lpp.begin(),lpp.end());
  erase(i);
  nb_insert--;
}

// Look for the first INSERT tag and return its prosodic parameters
bool LPhonemePlus::get_param_insert(double& init_f0, double& ambitus, double& speed)
{
  // Search insertion prosodic parameters
  iterator i;
  for(i=begin(); i!=end(); i++)
	 if ((*i).get_phone()==";;INSERT")
		break;
  
  // Sanity check
  if (i==end())
	 return false;
  
  // Get prosodic parameter for the insertion  
  speed=i->get_duration();
  init_f0= i->get_pitch().begin()->get_freq();
  ambitus= (i->get_pitch().begin())->get_pos();
  return true;
}

// Output in the format of a pho file
ostream& 
operator<< (ostream& o, const LPhonemePlus& lp)
{
  copy(lp.begin(),lp.end(),ostream_iterator<PhonemePlus>(o,"\n"));
  return o;
}
