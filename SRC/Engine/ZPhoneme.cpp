/*
 * File:    zphoneme.cpp
 * Purpose: Phoneme properties: zscores and voicing properties
 * Author: V. Pagel ( pagel@tcts.fpms.ac.be )
 * Version : 0.99
 * Time-stamp: <1999-04-22 15:07:15 pagel>
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
 *  19/03/98 : Renamed from Zscore to ZPhoneme, remove prosody generation
 *             the role is limited to Phoneme properties
 *  22/04/99 : for uniformity, comments begin with '##'
 */
#include "ZPhoneme.hpp"
#include "PitchPoint.hpp"
#include "VpError.hpp"

// Initialize the zscores with means and standard dev, and other phoneme info
ZPhoneme::ZPhoneme(istream& zs )
{
  char line[255];
  while(zs.getline(line,sizeof(line)))
	 {
		int pos=0;
		
		// Check if it's a comment
		sscanf(line," ##%n",&pos);
		if (pos==0)
		  {
			 double avg;
			 double std;
			 char phonename[255];
			 
			 // Skip empty lines or non conform ones
			 if (sscanf(line," %s %lf %lf %n", phonename, &avg, &std, &pos) == 3)
				{
				  ZPhone zf;
				  zf.zratio=Zratio(avg,std);
				  zf.flags= &line[pos];
				  insert( ZPhoneme::value_type(Phoneme(phonename),zf) );
				}
		  }
	 }
}

// Check if a flag belongs to the properties
bool 
ZPhoneme::is_a(const Phoneme& ph,const char a_flag) const
{
  const_iterator position= find(ph);
  if (position==end())
	 fatal_message(-1,"Unknown Phoneme\n");
  
  Flags fl=(*position).second.flags;
  return  fl.find(a_flag) != (unsigned) -1;
}

// Check if at least one flag belongs to the properties
bool 
ZPhoneme::is_a(const Phoneme& ph,const string& flags) const
{
  const_iterator position= find(ph);
  if (position==end())
	 fatal_message(-1,"Unknown Phoneme\n");
  Flags fl=(*position).second.flags;
	for(size_type i=0; i<flags.length(); i++)
	  {
		 if ( fl.find(flags[i]) != (unsigned) -1)
			return true;
	  }
	return false;
}

// Search the zscore of a phoneme
const Zratio& 
ZPhoneme::zscore(const PhonemePlus& pp) const
{
  const_iterator position= find( pp.get_phone() );

  if (position==end())
	  	fatal_message(-1,"Unknown Phoneme!?!\n");

  return (*position).second.zratio ;
}
