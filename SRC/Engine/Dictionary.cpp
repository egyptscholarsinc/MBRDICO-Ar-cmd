/*
 * File:    dictionary.cpp
 * Purpose: general purpose dictionary ( string key, string value )
 * Author: Vincent Pagel ( pagel@tcts.fpms.ac.be )
 * Version : 0.99
 * Time-stamp: <1999-04-22 15:58:18 pagel>
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
 *  11/03/98 : Created
 */

#include <fstream>
using namespace std;				  // Visual C++

#include "VpError.hpp"
#include "Dictionary.hpp"

// Read the dico
Dictionary::Dictionary(istream& dico)
{
  char headword[255];
  char transcrip[255];
  
  // Eats leading comment
  dico >> ws;
  while (dico.peek() == '#')
	 {
		dico.getline(transcrip,sizeof(transcrip));
		dico >> ws;
	 }
  
  // Get the word
  while(dico.getline(headword,sizeof(headword),' '))
	 { // Get its transcription on the rest of the line
		dico.getline(transcrip,sizeof(transcrip));
		insert(Dictionary::value_type(string(headword),string(transcrip)));
	 }
}

// Search a word in the dictionary
bool 
Dictionary::search(const string& word, string& result) const
{
  Dictionary::const_iterator position= find(word);
  if (position==end())
	{
	  	//fatal_message(-1,"Unknown Word %s\n",word);
	  return false;
	}

 result=(*position).second;
 return true;
}

// Search a word in  a phonologic dictionary
bool 
Dictionary::search(const string& word,  LPhonemePlus& lppresult) const
{
  string result;
  
  if (search(word,result))
	 {
		const char* temp=result.c_str();
		lppresult.ReadPhonologic(temp);
		return true;
	 }
  else
	 return false;
}
