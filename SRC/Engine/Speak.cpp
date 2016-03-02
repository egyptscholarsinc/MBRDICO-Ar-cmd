/*
 * File:    Speak.cpp
 * Purpose: phonetize and sprinkles with prosodic markers for a Mbrola ready sentence
 * Author:  Vincent Pagel ( pagel@tcts.fpms.ac.be ) 
 * Version : 0.99
 * Time-stamp: <1999-06-25 11:02:24 pagel> 
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
 *  19/03/98 : Tone and Prosody merged here to circumvent language dependent processes
 *  01/04/98 : Trie based letter to sound module added
 *  06/10/98 : Compiled tries are replaced with interpreted decision trees
 *  26/04/99 : Spanish and Dutch are a clone of American (because of lexical 
 *             accents). Tokenize digits together to utter numbers
 */

#include <stdio.h>
#include <list>
#include <algorithm>
#include <ctype.h>

#include "Speak.hpp"
#include "SpeakFrench.hpp"
#include "SpeakAmerican.hpp"
#include "SpeakArabic.hpp"

#include "PhonemePlus.hpp"
#include "VpError.hpp"

// Constructor with an initialization file
// Return polymorphic Speak heir
Speak* load_Speak(const char* ini_file)
{
  ifstream ini(ini_file);
  if (!ini.is_open())
	 fatal_message(-1,"Speak initialization fails: %s\n",ini_file);	

  // First param indicate the language
  char lang_name[255];
  ini.getline(lang_name, sizeof(lang_name) );

  char zscore_name[255];
  ini.getline(zscore_name, sizeof(zscore_name) );

  char except_name[255];
  ini.getline(except_name, sizeof(except_name) );

  char tree_name[255];
  ini.getline(tree_name, sizeof(tree_name) );

  char mbrola_dba[255];
  ini.getline(mbrola_dba, sizeof(mbrola_dba) );
  ini.close();

  ifstream zscore(zscore_name);
  if (!zscore.is_open())
	 fatal_message(-1, "Speak initialization fails: %s\n", zscore_name);	

  ifstream except(except_name);
  if (!except.is_open())
	 fatal_message(-1, "Speak initialization fails: %s\n", except_name);	
  
  ifstream tree(tree_name);
  if (!tree.is_open())
	 fatal_message(-1, "Speak initialization fails: %s\n", tree_name);	

  Speak* my_speak= new_Speak(lang_name, zscore, except, tree, mbrola_dba);

  zscore.close();
  except.close();
  tree.close();
  
  return my_speak;
}

// Constructor from streams. Return polymorphic heir of Speak
Speak* new_Speak(const char* lang_name,   // ( Spanish, American and so on)
						istream& zscore,         // Phoneme Durations
						istream& except,      // exception for letter2phoneme
						istream& tree,       // decision tree for letter2phoneme
						const char* mbrola_dba) // mbrola databases
{
  Speak* my_speak;
  if (strcmp(lang_name, "American")==0)
	 my_speak= new SpeakAmerican(zscore, except, tree, mbrola_dba);
  else if (strcmp(lang_name, "Arabic")==0)
	 my_speak= new SpeakArabic(zscore, except, tree, mbrola_dba);
  else if (strcmp(lang_name, "Dutch")==0)
	 my_speak= new SpeakAmerican(zscore, except, tree, mbrola_dba);
  else if (strcmp(lang_name, "French")==0)
	 my_speak= new SpeakFrench(zscore, except, tree, mbrola_dba);
  else if (strcmp(lang_name, "Spanish")==0)
	 my_speak= new SpeakAmerican(zscore, except, tree, mbrola_dba);
  else
	 {
		fatal_message(-1,"Unknown language %s\n", lang_name);
		my_speak= (Speak*) NULL; // to please the compile
	 }
  return my_speak;
}

// constructor with a Zscore file , and exception dictionary
// and a letter-to-sound set of rule
Speak::Speak(istream& zscore, istream& exception, istream& decision, const char* dba):rhythm(new ZPhoneme(zscore)),dico(new Dictionary(exception))
{
  l2p= load_Letter2Phone(decision);
  strcpy(mbrola_database,dba);
}

Speak::~Speak()
{
  if (rhythm) delete rhythm;
  if (dico) delete dico;
  if (l2p) delete l2p;
}

void 
Speak::transcribe(LPhonemePlus& lpp, 
						const char* target, 
						double f0_init,
						double f0_ambitus,
						double speed)
{
  dic_or_rules(lpp,target);
  utter(lpp, f0_init, f0_ambitus, speed);
}

// Grapheme to Pho file.... insert the target from INSERT tag
void
Speak::transcribe_insert(LPhonemePlus& lpp, const char* target)
{ 
  double speed,init_f0,ambitus;
  lpp.get_param_insert(init_f0,ambitus,speed);
  
  LPhonemePlus result;
  transcribe( result, target, init_f0, ambitus, speed);
  
  // Insert the result, then remove the INSERT marker
  lpp.insert_target(result);
}


// From the word to the phonetic transcription 
void
Speak::dic_or_rules(LPhonemePlus& lpp,	// Result: phonemic transcription
						  const char* target) // String + tag to transcribe
{
  LToken lt;
  tokenize(lt, target);
  
  // Trancribe each token
  for(LToken::const_iterator i=lt.begin(); i!=lt.end(); i++)
	 {
		// Need a "table of tags"
		string tag= i->get_tag();
		
		if (!dico->search(i->get_word(),lpp))
		  {
			 l2p->transcribe(lpp, i->get_word(), &tag); 
		  }
	 }
}

// From the phonetic transcription to the PHO file
void
Speak::utter(LPhonemePlus& lpp,       // Result of the transcription
				 double f0_init,    // Initial freq
				 double f0_ambitus, // F0 declination
				 double speed)      // Speed ratio
{
  double coefdur=thonification(lpp);
  prosodification(lpp, f0_init, f0_ambitus, speed*coefdur);
}


// Local definition of a separator .... tune it for your needs
static bool
is_a_sep(int c)
{
  if ( ((c>31) && (c<48) && (c!=39))  ||   //  32 ! 33 "" 34 # 35 $ 36 % 37 & 38 ' 39 ( 40 ) 41 * 42 + 43 , 44 - 45 . 46 / 47 
		 ((c>57) && (c<65)) ||    // : 58 ; 59 < 60 = 61 > 62 ? 63 @ 64
		 (c==91)            ||    // [ 91 
	    ((c>92) && (c<97)) ||    // ] 93 ^ 94 _ 95 ` 96 
		 ((c>122) && (c<192)))    //
	 return true;

  return false;
}

// Local definition of a numeric .... tune it for your needs
static bool
is_a_digit(int c)
{
  return (c>='0' && c<='9');
}

// Generic version
void
Speak::tokenize( LToken& lt, const char* target) const
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
		// Digits are kept together in a block
		bool digit_sequence= is_a_digit(target[pos]);

		while  ( !is_a_sep(target[pos]) &&
					(target[pos]!= 0 )     &&
					(is_a_digit(target[pos])==digit_sequence))
		  token+= tolower(target[pos++]);
		
		// Finito !
		if (token.empty())
		  break;
		
		lt.push_back( Token(token,tag) );
		// Reset the tag
		tag=""; token="";
	 }
}
