/*
 * File:    LToken.cpp
 * Purpose: List of tokens ( word and grammatical tag )
 * Author:  Vincent Pagel ( pagel@tcts.fpms.ac.be ) 
 * Version : 0.99
 * Time-stamp: <1999-02-01 13:06:57 pagel> 
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
 *  30/01/99 : Created
 */
#ifndef LTOKEN_H
#define LTOKEN_H

#include <list>
using namespace std;

class Token
{
public:
  Token() {}
  Token(const string& word,const string& tag):word(word),tag(tag) {}
  
  const string& get_word() const { return word; }
  const string& get_tag() const  { return tag; }

  // To please Visual C++ STL lists... but not implemented
  bool operator<(const Token& b) const;
  bool operator>(const Token& b) const;
  bool operator==(const Token& b) const;
  bool operator!=(const Token& b) const;
  
protected:
  string word;
  string tag;
};


class LToken: public list<Token>
{
public:
  LToken() {}
};

#endif
