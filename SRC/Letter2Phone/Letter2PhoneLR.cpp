/*
 * File:    letter2phoneLR.cpp
 * Purpose: transcribe a word letter by letter with a decision tree ( Left to right direction)
 * Author:  Vincent Pagel ( pagel@tcts.fpms.ac.be )
 * Version : 0.99
 * Time-stamp: <2000-03-17 11:29:50 pagel>
 * 
 * Copyright (c) 1998-2000 Faculte Polytechnique de Mons (TCTS lab)
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
 * 21/06/99: Created from Letter2Phone.cpp
 */

#include "Letter2PhoneLR.hpp"

// transform a string into a phonemic transcription
void 
Letter2PhoneLR::transcribe( LPhonemePlus& lpp,   // result
									 const string& target, // string to transcribe
									 const string * tags) const  // associated grammatical tags table
{
  int i; // general purpose index (Visual C++ doesn't respect the standard with FOR definition
  Feature boundary("-");
  Feature silence("_");
  
  //
  // Build Graphemic vector
  //
  Feature grapheme[100]; // graphemic feature, including leading and trailing '-'
  int nb_grapheme;
  int tot_grapheme;
  
  // initial "-" for left boundary
  for(tot_grapheme=0; tot_grapheme<left_grapheme; tot_grapheme++)
	 grapheme[ tot_grapheme ]= boundary;
  
  // one feature for each letter in the original string
  string temp_str("1");
  for(nb_grapheme=0; nb_grapheme < (signed) target.size(); nb_grapheme++, tot_grapheme++)
	 {
		temp_str[0]= target[nb_grapheme];
		grapheme[ tot_grapheme ]= Feature(temp_str);
	 }
  
  // trailing "-" for right boundary
  for(i=0 ; i<right_grapheme; i++, tot_grapheme++)
	 grapheme[ tot_grapheme ]= boundary;
  
  //
  // Initialize the solution
  //
  Value phoneme[100];    // Computed solution, including trailing '-'
  int nb_phoneme;
  for (nb_phoneme=0; nb_phoneme< nb_feedback; nb_phoneme++)
	 phoneme[nb_phoneme]= boundary;
  
  //
  // Constant part of the decision vector
  //
  int feature_index=0; 
  
  // Build the constant part
  for (i=0; i<nb_skip; i++)
	 data[feature_index++]= Feature(tags[i]);
  
  // Transcribe from left to right
  for(i=0; i<nb_grapheme; i++)
	 {
		// Leave the beginning untouched through the loop, contain external
		//features such as PART_OF_SPEECH 
		feature_index= nb_skip;
		
		/* LLLTRRRR */
		for(int j=0; j<left_grapheme+right_grapheme+1; j++)
		  data[feature_index++]= grapheme[i+j];
		
		/* Phonemic loop */
		for(int k=0; k<nb_feedback; k++)
		  data[feature_index++]= phoneme[nb_phoneme-1-k];
				
		// transcribe the vector ! 
		Value result= my_decision->run(data);
		
		// progress if non null transcription
		if (result != silence)
		  {
		    phoneme[nb_phoneme++]= result;
		    
		    // demultiply pseudo phonemes against '+' separator
		    string result_str= result.str();

		    string::size_type cur_pos=0;
		    string::size_type pos_pseudo;
		    do
		      { 
			pos_pseudo= result_str.find ('+', cur_pos);
			
			// Add the phoneme or part of pseudo phone
			lpp.push_back(PhonemePlus( result_str.substr(cur_pos,pos_pseudo) ));
			cur_pos= pos_pseudo+1;
		      }
		    while (pos_pseudo != result_str.npos);
		  }
	 }
}
