/*
 * File:    Speak.hpp
 * Purpose: phonetize and sprinkles with prosodic markers (common ancestor)
 * Author: Vincent Pagel ( pagel@tcts.fpms.ac.be ) 
 * Version : 0.99
 * Time-stamp: <1999-06-23 12:32:50 pagel>
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
 */

#ifndef SPEAK_H
#define SPEAK_H

#include <stdio.h>
#include "ZPhoneme.hpp"
#include "LPhonemePlus.hpp"
#include "Dictionary.hpp"
#include "Letter2Phone.hpp"
#include "LToken.hpp"

// Constructor from streams
// Return polymorphic heir of Speak
class Speak* new_Speak(const char* lang_name,   // ( Spanish, American and so on)
							  istream& zscore,         // Phoneme Durations
							  istream& exception,      // exception for letter2phoneme
							  istream& decision,       // decision tree for letter2phoneme
							  const char* mbrola_dba); // mbrola databases

// Constructor with an initialization file
// RETURN A POLYMORPHIC LANGUAGE DEPENDENT SPEAK OBJECT
class Speak* load_Speak(const char* ini_file); 

class Speak
{
public:

  Speak(istream& zscore,         // Phoneme Durations
		  istream& exception,      // exception for letter2phoneme
		  istream& decision,       // decision tree for letter2phoneme
		  const char* mbrola_dba); // mbrola databases

  virtual ~Speak();		// virtual because some heir may want to implement extra members
  
  // Grapheme to phoneme
  void dic_or_rules(LPhonemePlus& lpp, const char* target);
  
  // Phoneme to Pho file
  void utter(LPhonemePlus& lpp, double init_f0=130.0, double f0_ambitus=30.0, double speed=1.0);

  // Grapheme to Pho file
  void transcribe(LPhonemePlus& lpp, 
						const char* target, 
						double f0_init=130.0,
						double f0_ambitus=30.0,
						double speed=1.0);

  // Grapheme to Pho file.... insert the target from INSERT tag
  void transcribe_insert(LPhonemePlus& lpp, const char* target);
  
  // Repository for the related mbrola database
  const char* get_dba() const { return mbrola_database; }

  // Search a word in the exception dictionary
  bool dico_search(LPhonemePlus& lpp,const char* target) const;

  // Three language dependents: split into tokens, put tones, generate duration and pitch
  virtual void tokenize(LToken& ltoken, const char* target) const; // generic version is defined
  virtual double thonification(LPhonemePlus& lpp) const =0;        // no generic
  virtual void   prosodification(LPhonemePlus& lpp,
											double init_f0, double ambitus, double speed) const =0;
  
protected:
  ZPhoneme* rhythm;
  Dictionary* dico;
  Letter2Phone* l2p;
  char mbrola_database[255];
};

#endif
