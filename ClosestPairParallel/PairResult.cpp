// -*- C++ -*-

/*
 * PairResult.cpp
 *
 * An easy place for you to store the temporary solutions
 * you find along the way.
 */

#include <cstdlib>
#include <iostream>
#include <iostream>
#include <fstream>
#include <limits>
#include "PairResult.h"

using namespace std;

// DO NOT MODIFY THIS FILE !!!!
// (the Auto-Grader will use the original version of this file,
// so any modifications you make here will be discarded before
// your assignment is graded)


// simple constructor, distance defaults to infinity
PairResult::PairResult() {
  distance = std::numeric_limits<double>::infinity();
  pointOne = pointTwo = NULL;
}

void PairResult::print() {

  if ((pointOne == NULL) || (pointTwo == NULL)) {
    std::cout << "  Invalid Result: points not initialized" << std::endl;
    return;
  }

  std::cout.setf(ios::fixed);
  std::cout.precision(2);
  std::cout << "  Result: the closest pair has distance = " << distance << " (between ";
  pointOne->print();
  std::cout << " and ";
  pointTwo->print();
  std::cout << std::endl;

}

/* 
 * This method is provided to make your life easier, but you are 
 * not obligated to use it.
 */
void PairResult::copy(PairResult *copyMe) {

  distance = copyMe->distance;
  pointOne = copyMe->pointOne;
  pointTwo = copyMe->pointTwo;

}
