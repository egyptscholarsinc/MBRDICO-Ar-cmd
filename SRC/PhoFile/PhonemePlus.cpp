/*
 * File:    PhonemePlus.cpp
 * Purpose: a Phoneme, its duration, its pitchpoints, and its prosodic markers
 * Author: Vincent Pagel ( pagel@tcts.fpms.ac.be )
 * Version : 0.99
 * Time-stamp: <1999-06-23 12:37:49 pagel>
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

#include "VpError.hpp"
#include "PhonemePlus.hpp"

PhonemePlus::PhonemePlus(const string& phoneme)
{
  size_t l= phoneme.size();

  // Collect accent in the prosody marker
  if (phoneme[l-1] == '1')
	 {
		prosody+='1';
		l--;
	 }
  phone= phoneme.substr(0,l);
}

void
PhonemePlus::erase()
{  pitch.erase(pitch.begin(),pitch.end()); }


// Parse a line in a .pho file
ifstream& 
in_phofile(ifstream& o, PhonemePlus &phonplus)
{
  char line[200];
  
  if (o.getline(line,sizeof(line)))
	 {
		int comment=0;
		size_t leading_blank=0;
		int insert=0;
				
		sscanf(line," %n",&leading_blank);
		char* rest= &line[leading_blank];
		sscanf(rest," ;%n", &comment);

		sscanf(rest," ;; INSERT%n", &insert);
		
		if (insert!=0)
		  {
			 // Insertion point of a carrier sentence
			 phonplus.phone=Phoneme(";;INSERT");
			 // Fetch the parameters
			 float f0, ambitus, speed;
			 sscanf(&rest[insert]," %f %f %f", &f0, &ambitus, &speed);
			 
			 // Put a dummy pitch point :-=
			 phonplus.append_pitch( PitchPoint(ambitus,f0) );
			 phonplus.duration=speed;

			 return o;
		  }
		
		// Read next line
		if ( (comment!=0) ||
			  (leading_blank==strlen(line)))
		  return in_phofile(o,phonplus);
		
		char name[200];
		int position=0;
		int val=sscanf(rest,"%s %lf%n",name,&phonplus.duration,&position);
		
		if (val!=2)
		  fatal_message(ERROR_UNKNOWNCOMMAND, "Error in %s\n", rest);
		
		phonplus.phone=  Phoneme(name);

		int new_pos;
		float pos,f0;
      while ( (sscanf(&rest[position]," ( %f , %f ) %n", &pos, &f0, &new_pos)==2)
				  || (sscanf(&rest[position]," %f %f%n", &pos, &f0, &new_pos)==2))
		  {
			 PitchPoint pp(pos,f0);
			 
			 phonplus.pitch.push_back(pp);
			 position+=new_pos;
		  }
      
      /* Check for residual characters in the line */
      if (sscanf(&rest[position],"%*s")!=-1)
		  fatal_message(ERROR_UNKNOWNCOMMAND,
							 "Fatal error in line:%s\n"
							 "At the pitch pair:%s????\n",
							 rest,&rest[position]);
	 }
  return o;
}


// Output in .pho format
ostream& 
operator<< (ostream& o, const PhonemePlus& p)
{
  // Indicate prosodic flags as comments
  if ( p.get_prosody().length()!=0)
	 o << "; Proso " << p.get_prosody() << endl;

  o << p.get_phone() << " " << p.get_duration() << " " << p.get_pitch() << " ";
  return o;
}

