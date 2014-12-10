// -*- C++ -*-

/*
 * PairResult.h
 *
 * Just a convient place to store your solution.
 * We have kept everything public to make the coding simpler.
 */

#include <cstdlib>
#include <iostream>
#include <iostream>
#include <fstream>
#include "Point.cpp"

using namespace std;

// DO NOT MODIFY THIS FILE !!!!
// (the Auto-Grader will use the original version of this file,
// so any modifications you make here will be discarded before
// your assignment is graded)

class PairResult {

 public:

  // all solutions need to fill these 3 fields
  double distance;
  Point *pointOne;
  Point *pointTwo;
  
  // constructor gives you a new solution, all fields set to 0
  PairResult();
  
  void print();

  // For Your Convenience:
  // you do not have to use this, but you are welcome to
  void copy(PairResult *copyMe);
};
