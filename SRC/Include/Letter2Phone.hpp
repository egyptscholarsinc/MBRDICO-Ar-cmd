/*
 * File:    letter2phone.h
 * Purpose: transcribe a word, from a decision tree
 * Author:  Vincent Pagel ( pagel@tcts.fpms.ac.be )
 * Version : 0.99
 * Time-stamp: <1999-06-24 16:43:31 pagel>
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
 * 08/10/98: Created
 * 20/01/99: use string instead of char*
 */

#ifndef LETTER2PHONE_H
#define LETTER2PHONE_H

# include <iostream>    

#include "DecisionTree.hpp"
#include "LPhonemePlus.hpp"
#include <vector>

// Constructor with an initialization file
// RETURN A POLYMORPHIC DIRECTION DEPENDENT SPEAK OBJECT
// (everything depends on the 1st line (the learning vector format)
class Letter2Phone* load_Letter2Phone(istream& decision_stream); 

class Letter2Phone
{
 public:
  // Constructor reads info and a decision tree from the stream
  Letter2Phone(istream& decision_stream, 
					int nb_skip, int left_grapheme, int right_grapheme, int nb_feeback);
  
  virtual ~Letter2Phone();
  
  // transform a string + grammatical tag into a phonemic transcription
  virtual void transcribe(LPhonemePlus& lpp, const string& target, const string * tags) const=0;
  
protected:
  // How to construct the vector presented to the decision tree
  int  nb_skip;
  int  left_grapheme;
  int  right_grapheme;
  int  nb_feedback;
   
  int vector_size;     // size of the decision vector below
  FeatureVector data;  // Used by the transcribe method
  Decision* my_decision;  // The native decision tree
};

#endif
