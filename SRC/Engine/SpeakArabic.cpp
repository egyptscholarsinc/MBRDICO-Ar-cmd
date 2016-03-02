/*
 * File:    SpeakArabic.cpp
 * Purpose: phonetize and sprinkles with prosodic markers for a Mbrola ready sentence
 *          inherit for Arabic
 * Author:  Nawfal Tounsi ( tounsi@tcts.fpms.ac.be ) 
 * Version : 0.99
 * Time-stamp: <1999-06-23 12:21:50 pagel> 
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

#include "SpeakArabic.hpp"
#include "PhonemePlus.hpp"
#include "VpError.hpp"

// constructor with a Zscore file , and exception dictionary
// and a letter-to-sound set of rule
SpeakArabic::SpeakArabic(istream& zscore, istream& exception, istream& decision, const char* dba): Speak(zscore,exception,decision,dba)
{
  strcpy(mbrola_database,dba);
}

// Local definition of a separator .... tune it for your needs
static bool
is_a_sep(int c)
{
  if ( ((c>31) && (c<48)) ||   //  32 ! 33 "" 34 # 35 $ 36 % 37 & 38 ' 39 ( 40 ) 41 * 42 + 43 , 44 - 45 . 46 / 47 
		 ((c>57) && (c<65)) ||    // : 58 ; 59 < 60 = 61 > 62 ? 63 @ 64
		 (c==91)            ||    // [ 91 
	    ((c>92) && (c<97)) ||    // ] 93 ^ 94 _ 95 ` 96 
		 ((c>122) && (c<126)) ||
		 ((c>126) && (c<192)))   // ~ is 126
	 return true;

  return false;
}

// Tokenization for Arabic -> no tag and no upper to lower conversion
void
SpeakArabic::tokenize( LToken& lt, const char* target) const
{
  int pos=0;
  string token;
  string tag; 
  
  while (1)
	 {
		// Skip blanks
		while ( is_a_sep(target[pos]) &&
				  (target[pos]!= 0 ))
		  pos++;
		
		// A grammatical tag begins with '\' !
		if (target[pos]=='\\')
		  {
			 pos+=1;
			 while  ( !is_a_sep(target[pos]) &&
						 (target[pos]!= 0 ))
				tag+= target[pos++];
		  }
		
		// Skip blanks
		while ( is_a_sep(target[pos]) &&
				  (target[pos]!= 0 ))
		  pos++;
		
		// Read the string, transform to lower case 
		while  (  !is_a_sep(target[pos]) &&
					 (target[pos]!= 0 ))
		  token+= target[pos++];
		
		// Finito !
		if (token.empty())
		  break;
		
		lt.push_back( Token(token,tag) );
		// Reset the tag
		tag=""; token="";
	 }
}


// Spread accents and return basic speed (the shortest the word, the slowest the pace)
double 
SpeakArabic::thonification(LPhonemePlus& lpp) const
{
	LPhonemePlus::iterator last_voy=  lpp.end();  // last vowel of the word
	LPhonemePlus::iterator first_voy= lpp.end(); // first vowel of the word
	LPhonemePlus::iterator last_phon;           // last phoneme treated

	int nbsyll=0;				 // number of syllables
	double coefsyll;			// rhythm coefficient depending on the nb of syll
	int j =0;               // to delete the "shedda" phoneme

	// Count number of syllables
	for(LPhonemePlus::iterator i=lpp.begin(); i!=lpp.end(); i++ , j++)
	{
	  // Remove the shedda (accent)
	  if ((*i).get_phone() == "~")
		 {
			(*last_phon).append_prosody("1");
			lpp.erase(i);
			i=last_phon;
		 }
	  else
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

			// In a sequence of 2 consonants, lengthen the previous one
			if ( nbsyll &&
				  !(rhythm->is_a( (*i).get_phone() ,'V')) && 
				  !(rhythm->is_a( (*last_phon).get_phone() ,'V')))
			  (*last_phon).append_prosody(":");

			last_phon=i;
		 }
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
SpeakArabic::prosodification(LPhonemePlus& lpp, double init_f0, double ambitus, double speed) const
{
  double cur_f0= init_f0;
  double cur_dur= 0.0;
  
  LPhonemePlus::iterator i=lpp.begin();
  
  // List is void ?
  if (i==lpp.end())
	 return;
  
  (*i).append_pitch( PitchPoint(0.0,init_f0-10.0)); // initial pitch point
  
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
				  pp.append_pitch( PitchPoint(20.0,init_f0+10.0) ); // Small Raise
				  zratio += 0.2;					  // A bit longer
				  break;
				  
				case '&':	 // Final shortening on last syllable
				  zratio -=0.4;	   // Slight acceleration
				  cur_dur-=0.4;
				  pp.append_pitch( PitchPoint(80.0,init_f0-30.0));
				  break;
				  
				case '>':	// End of the word, falling tone and reset
				  // Lower pitch by 60Hz
				  pp.append_pitch( PitchPoint(100.0,init_f0-60.0));
				  
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
