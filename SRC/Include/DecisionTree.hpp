/*
 * File:    decision_tree.h
 * Purpose: parse and run decision char* based trees 
 * Author:  Vincent Pagel ( pagel@tcts.fpms.ac.be )
 * Version : 0.99
 * Time-stamp: <1999-04-22 15:30:47 pagel>
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
 * 04/10/98: Created
 */

#ifndef DECISION_TREE_H
#define DECISION_TREE_H

#include  <stdio.h>
#include  <list>
#include  <vector>
# include <iostream>
using namespace std;

#include "Feature.hpp"

typedef Feature Value;          // return value of a decision
typedef Feature* FeatureVector; // vector to classify

// Common method for constructing either a SwitchDecision or a TerminalDecision
class Decision* load_Decision(istream& in);

// Abstract Type, a decision may be terminal (no more choice) or 
// wipe through recursive switch statements
class Decision 
{
public:
  // Destructor for abtract type
  virtual ~Decision() {};

  // Take a decision according to a vector of features
  virtual const Value& run(const FeatureVector& f) const =0;
  
  // Number of nodes
  virtual int size() const =0;
  
  // virtual entry point to print all the derived classe (see operator <<)
  virtual void display( ostream& o, int depth) const =0;
  
protected:

  // Function for indentation of recursive case
  static void tabulate(ostream& o, int depth)
	 {
		o << "\n";
		for(int i=0; i<depth; i++)
		  o << " ";
	 }
};


// non virtual entry point to print all the derived class 
ostream& operator << (ostream& o,  const Decision& d);



// 
// Terminal node in the decision tree
//
class TerminalDecision : public Decision 
{
public:

  // Constructor -> read a token
  TerminalDecision(const Value& token);
  
  // Take a decision according to a vector of features
  const Value& run(const FeatureVector& f) const;
  
  // Number of nodes
  int size() const;
  
  // Recursively display the tree
  void display( ostream& o, int depth) const;

protected:
  Value return_value;			  // the decision at last

};

// Recursive decision tree
class SwitchDecision : public Decision 
{
public:
  // Constructor from a data stream
  SwitchDecision(istream& in_file);
  
  // recursive destructor
  virtual ~SwitchDecision();
  
  // Take a decision according to a vector of features
  virtual const Value& run(const FeatureVector& f) const;
  
  // Number of nodes
  virtual int size() const;
  
  // Recursively display the tree
  virtual void display( ostream& o, int depth) const ;
  
protected:
  // A case statement -> the feature value to match and corresponding decision
  typedef pair<Feature, Decision*> Case;
  
  // function to display a case statement
  static void Case_display(ostream& o, const Case& c, int depth)
	 {
		tabulate(o, depth);
		o << "case " << c.first << ":";
		c.second->display(o, depth) ;
	 }
  
  int feature_index;   // index of the feature to test against
  vector<Case> cases;  // the list of cases
  Value default_value; // default return value
};

#endif
