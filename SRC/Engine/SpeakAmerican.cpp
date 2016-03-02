/*
 * File:    SpeakAmerican.cpp
 * Purpose: phonetize and sprinkles with prosodic markers for a Mbrola ready sentence
 *          inherit for American
 * Author:  Vincent Pagel ( pagel@tcts.fpms.ac.be ) 
 * Version : 0.99
 * Time-stamp: <1999-06-23 12:19:21 pagel> 
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
 *  20/01/99 : Created
 *  19/05/99 : Philippe Devallois -> bug with "keep F0 in sensible limits"
 */

#include <stdio.h>
#include <list>
#include <algorithm>

#include "SpeakAmerican.hpp"
#include "PhonemePlus.hpp"
#include "VpError.hpp"

// constructor with a Zscore file , and exception dictionary
// and a letter-to-sound set of rule
SpeakAmerican::SpeakAmerican(istream& zscore, istream& exception, istream& decision, const char* dba): Speak(zscore,exception,decision,dba)
{
  strcpy(mbrola_database,dba);
}

// Spread accents and return basic speed (the shortest the word, the slowest the pace)
double 
SpeakAmerican::thonification(LPhonemePlus& lpp) const
{
	LPhonemePlus::iterator last_voy=  lpp.end();  // last vowel of the word
	LPhonemePlus::iterator first_voy= lpp.end(); // first vowel of the word
	LPhonemePlus::iterator last_phon;           // last phoneme treated

	int nbsyll=0;				 // number of syllables
	double coefsyll;			// rhythm coefficient depending on the nb of syll

	// Count number of syllables
	for(LPhonemePlus::iterator i=lpp.begin(); i!=lpp.end(); i++)
	{
	  if (rhythm->is_a( (*i).get_phone() ,'V'))
		 {
			// First vowel of the word
			if (nbsyll==0)	
			  first_voy=i;
			
			// memorize last vowel of the word
			last_voy=i;
			nbsyll++;
		 }
	  
	  // Vowel followed by a vowel lengthener phoneme (voiced consonants )
	  if ( (rhythm->is_a((*i).get_phone() ,'Z')) &&
			 (last_voy==last_phon))   // Last one was a vowel
		 (*last_voy).append_prosody(":");
	  last_phon=i;
	}
	
	if (last_voy!=lpp.end())
	  {
		 // Diacritics = and & can be cumulated in the case of monosyllabics
		 
		 // Final lengthening
		 (*last_voy).append_prosody("&");
		 
		 // Final pitch
		 lpp.back().append_prosody(">");
	  }
	
	// The more syllable, the faster the pace
	switch (nbsyll)
	  {
	  case 1: coefsyll=1.0;
		 break;
	  case 2: coefsyll=0.95;
		 break;
	  case 3: coefsyll=0.90;
		 break;
	  case 4: coefsyll=0.88;
		 break;
	  default: coefsyll=0.86;
	  }
	return coefsyll;
}


// Give durations and pitch points from phonological marks
void 
 SpeakAmerican::prosodification(LPhonemePlus& lpp, double init_f0, double ambitus, double speed) const
{
  double cur_f0= init_f0;
  double cur_dur= 0.0;
  
  LPhonemePlus::iterator i=lpp.begin();
  
  // List is void ?
  if (i==lpp.end())
	 return;
  
  (*i).append_pitch( PitchPoint(0.0,init_f0-ambitus*0.3)); // initial pitch point
  
  for(; i!=lpp.end(); i++)
	 {
		PhonemePlus& pp=(*i);
		
		Zratio zr=rhythm->zscore(pp);	  
		double average= zr.first;
		double std= zr.second;
		string proso= pp.get_prosody();
		double zratio=cur_dur;
		
		for (size_t i=0; i < proso.size() ; i++)
		  {
			 char diacritic=proso[i];
			 
			 switch (diacritic)
				{
				case ':': // Lengthened vowel, local effect only
				  zratio += 0.2;				  // Slow down
				  break;
				  
				case '1': // Primary accent, small prominence and lengthening
				  pp.append_pitch( PitchPoint(20.0,init_f0+ambitus*0.3) ); // Small Raise
				  zratio += 0.2;					  // A bit longer
				  break;
				  
				case '&':	 // Final lengthening -> last syllable
				  zratio += 0.4;	  // Slow down
				  cur_dur+= 0.4;
				  pp.append_pitch( PitchPoint(80.0,init_f0-ambitus*0.8));
				  break;
				  
				case '>':	// End of the word, falling tone and reset
				  // Lower pitch by 40Hz
				  pp.append_pitch( PitchPoint(100.0,init_f0-ambitus));
				  
				  // Reset values for next word
				  cur_dur=0.0;
				  cur_f0=init_f0;
				  break;
				}
		  }  
		// Keep in sensible duration limits  
		if (cur_dur<-1)
		  cur_dur=-1;
		if (cur_dur>1)
		  cur_dur=1;
		
		// Keep sensible F0 limits
		if (cur_f0<init_f0/1.5)
		  cur_f0= init_f0/1.5;
		if (cur_f0>init_f0*1.5)
		  cur_f0=init_f0*1.5;
		
		pp.set_duration( (zratio*std+average)*speed );
	 }
}
