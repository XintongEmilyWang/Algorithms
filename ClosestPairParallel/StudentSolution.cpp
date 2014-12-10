// -*- C++ -*-

/*
 * StudentSolution.cpp
 *
 * HW 02, two ways of solving ClosestPair 
 *
 * THIS is the only file we will look at when we grade your homework.
 * All other changes you made to any other files will be discarded.
 */

#include <cstdlib>
#include <cilk/cilk.h>
#include <cilk/reducer_min.h>
#include <iostream>
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;
const double INF=numeric_limits<double>::infinity();

/* 
 * This method implements the brute force method of finding closest points.
 * Use this to test the correctness of the recursive O(nlogn) method on small sets.
 */
void solveClosestPairBrute(PointArray *points, PairResult *result) {
  int nPoints=points->size();
  result->distance=INF;
  if(nPoints==1){
    result->pointOne=points->getPoint(0);
    result->distance=INF;
  }else{
    for(int i=0;i<nPoints-1;i++){
      for(int j=i+1;j<nPoints;j++){
	Point *one=points->getPoint(i);
	Piont *two=points->getPoint(j);
	double dist=one->distance(two);
	if(dist<result->distance){
	  result->distance=dist;
	  result->pointOne=one;
	  result->pointTwo=two;
	}
      }
    }
  }

}

/* 
 * This is the recursive method that you will complete to solve
 * the closest pair problem. It should:
 *   (1) divide that splits the input sequence in approximately half 
 *   (2) recurse that recursively solves the two halves of the problem
 *   (3) combine that finds the solution to your input
 * The range of the array goes from (begin, end] (inclusive of begin, exclusive of end)
 */
void solveClosestPairRecurse(PointArray *points, int begin, int end, PairResult *result) {

}

/* 
 * This is the parallel version of our recrusive method.
 */


void solveClosestPairParallel(PointArray *points, int begin, int end, PairResult *result) {

}

