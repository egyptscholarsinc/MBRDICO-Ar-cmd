/*
 * File:    decision_tree.cpp
 * Purpose: read and execute decision tree
 * Author:  Vincent Pagel ( pagel@tcts.fpms.ac.be )
 * Version : 0.99
 * Time-stamp: <1999-02-22 10:12:55 pagel>
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
 * 06/10/98: Created from run_tree.c
 * 16/02/99: cases becomes a vector (spares memory)
 */

#include "DecisionTree.hpp"
#include "VpError.hpp"

#ifdef UNIX
# include <strings.h>
#endif 

// Common method for constructing either a SwitchDecision or a TerminalDecision
Decision* 
load_Decision(istream& in)
{
  char bracket;
  in  >> ws >> bracket; // eat white spaces, and opening bracket

  // Opening parenthesis
  if ( bracket != '[')
		fatal_message(-1,"Decision tree: Ooops opening bracket\n");

  return new SwitchDecision(in);
}

// Common method for displaying polymorphic decisions
ostream& 
operator << (ostream& o, const Decision& d)
{
  d.display(o,0);  // virtual function
  return o;
}

// Instanciation of a TERMINAL node
TerminalDecision::TerminalDecision(const Value& token): return_value(token)
{
}

const Value& 
TerminalDecision::run(const FeatureVector& f) const
{  return return_value; }

int
TerminalDecision::size() const
{ return 1; }

void
TerminalDecision::display( ostream& o, int depth) const 
{  
  tabulate(o, depth);
  o << "return " << return_value;  
}

// Instanciation of a RECURSIVE switch node
SwitchDecision::SwitchDecision(istream& in_file)
{
  // IMPORTANT: still using buffer of CHAR instead of STRING, because of >> operator behavior
  // with strings -> it requires some setlocale stuffs. As a matter of fact the french letter
  // e^ is still considered as a separator even in french or iso8859_1 mode !?!?! 
  // It prevents french decision trees :-( Anybody help?
  char buffer[100];
  
  // Read the attibute index to test
  in_file >> feature_index;
  if (feature_index==0)
	 fatal_message(-1,"SwitchDecision: Ooops, didn't read a feature\n");

  // Default return value
  in_file >> buffer;
  default_value= Feature(string(buffer));
  
  // Read the next case attrib
  while ( in_file >> buffer )
	 {
		// end of the switch, is the default field
		if (strcmp(buffer,"]")==0)
		  return;
		else
		  {
			 Feature attrib= Feature(string(buffer)); // Allocate the string
			 
			 in_file >> buffer;
			 if (strcmp(buffer,"[") == 0)
				cases.push_back( Case(attrib, 
											 new SwitchDecision(in_file)) ); // Recursive node
			 else
				cases.push_back( Case(attrib, 
											 new TerminalDecision(string(buffer))) );	 // Terminal node
		  }
	 }

  // Should never arrive here, and rather leave through "]"
  fatal_message(-1,"Decision tree: Ooops, unbalanced brackets in the decision tree\n");
}

// Recursively destroy 
SwitchDecision::~SwitchDecision()
{
 for(vector<Case>::const_iterator i= cases.begin() ; i != cases.end() ; i++)
	  delete (*i).second;
}

// Recursively run the decision from a vector of features
const Value& 
SwitchDecision::run(const FeatureVector& f) const
{
  for(vector<Case>::const_iterator i= cases.begin() ; i != cases.end() ; i++)
	 {
		// found the right case ? 
		// feature_index-1 because 0 was the solution during training
		if ( (*i).first == f[feature_index-1])
		  {
			 Decision* d= (*i).second;
			 return d->run(f);
		  }
	 }
  return default_value;
}

// Number of nodes
int 
SwitchDecision::size() const
{
  int tot=1;  // 1 for the default node

  // count one for the case test, and one for the terminal node
  for(vector<Case>::const_iterator i= cases.begin() ; i!=cases.end() ; i++)
	 tot+= ( 1 + (*i).second->size());

  return tot ;
}

// Recursively display the tree
void 
SwitchDecision::display( ostream& o, int depth) const 
{
  tabulate(o, depth);
  o << "switch (" << feature_index << ") {" ;
  
  
  for(vector<Case>::const_iterator i= cases.begin() ; i!=cases.end() ; i++)
	 Case_display(o, *i, depth+1);
  
  tabulate(o, depth+1);
  o << "default: return " << default_value;
  tabulate(o, depth);
  o << "}";
}
