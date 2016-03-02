/*
 * File:    letter2phone.cpp
 * Purpose: transcribe a word letter by letter with a decision tree
 * Author:  Vincent Pagel ( pagel@tcts.fpms.ac.be )
 * Version : 0.99
 * Time-stamp: <1999-06-24 17:08:30 pagel>
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
 * 19/05/99: bug report by Philippe Devallois -> vector_size
 */

#include "Letter2Phone.hpp"
#include "Letter2PhoneRL.hpp"
#include "Letter2PhoneLR.hpp"
#include "VpError.hpp"

// First line indicate the format of the learning vector ( LLLTRRRS )
// Allocate the right phonetizer depending on the direction of the transcription
Letter2Phone* load_Letter2Phone(istream& in)
{
  int position=0;
  char format[100];

  int left_grapheme=0;
  int right_grapheme=0;
  int nb_feedback=0;
  int nb_skip=0;

  // Have to decide the feedback direction first
  int nb_LRfeedback=0;
  int nb_RLfeedback=0;
  bool left_to_right;
  
  // Skip leading copyright notice
  int pos_comment;
  do
	 {
		in.getline(format,sizeof(format));
		
		// Check if it's a comment
		pos_comment=0;
		sscanf(format," ##%n",&pos_comment);
	 }
  while ( pos_comment!=0 );
  
  while ( format[position]!=0 )
	 {
		switch (format[position]) 
		  {
		  case 'L':
			 left_grapheme++; 
			 break;
		  case 'R':
			 right_grapheme++;
			 break;
		  case 'T': /* target, ignore for the moment. It's mostly visual */
			 break;
		  case 'P':   // P and Q are incompatible features
			 nb_RLfeedback++;
			 break;
		  case 'Q':
			 nb_LRfeedback++;
			 break;
		  case 'S':
			 nb_skip++;
			 break;
		  case ' ':
		  case 10:
		  case 12:
		  case 13:	  /*  Ignore blanks */
			 break;
		  default:
			 fatal_message(-1,"Unknown Attribute %c\n",format[position]);
			 break;
		  }
		position++;
	 }
  
  // Those flags are incompatible
  if (nb_RLfeedback*nb_LRfeedback!=0)
	 fatal_message(-1,"Can't apply LEFT and RIGHT feedback at the same time\n");
  
  // Decide the feedback direction
  if (nb_RLfeedback>nb_LRfeedback)
	 {
		left_to_right=false;
		nb_feedback=nb_RLfeedback;
	 }
  else
	 {
		left_to_right=true;
		nb_feedback=nb_LRfeedback;
	 }

  Letter2Phone* my_l2p;
  if (left_to_right)
    my_l2p= new Letter2PhoneLR(in, nb_skip, left_grapheme, right_grapheme, nb_feedback);
  else
    my_l2p= new Letter2PhoneRL(in, nb_skip, left_grapheme, right_grapheme, nb_feedback);

  return my_l2p;
}

Letter2Phone::Letter2Phone(istream& decision_stream,int ns, int lg, int rg, int nf): 
  nb_skip(ns),left_grapheme(lg),right_grapheme(rg),nb_feedback(nf),vector_size(ns+nf+lg+rg+1)
{
  // Decision tree
  my_decision= load_Decision(decision_stream);
  
  // a decision vector
  data= new Feature[vector_size];
}

Letter2Phone::~Letter2Phone()
{
  if (my_decision)
	 delete my_decision;
  
  if (data)
	 delete[] data;
}
