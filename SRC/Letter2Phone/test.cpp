/*
 * test.cpp
 *
 * Time-stamp: <1998-11-19 14:06:36 pagel>
 */

#include <strings.h>
#include <fstream.h>
#include <stdio.h>
#include "DecisionTree.hpp"

int main(int argc, char **argv)
{
  if (argc!=2)
	 {
		cerr << "Usage: " << argv[0] << " toto.tree" << endl;
		return 1;
	 }

  ifstream in_file(argv[1]);
  if (!in_file.is_open())
	 {
		cerr << "ca va mal\n";
		return 2;
	 }
  
  // header contains the vector's format
  char  format[255];
  in_file.getline(format,sizeof(format));
  
  Decision* my_decision= load_Decision(in_file);
  in_file.close();

  cout << *my_decision;
  cout << "\n the tree size :" << my_decision->size();
}
