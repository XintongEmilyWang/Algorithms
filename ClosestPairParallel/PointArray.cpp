// -*- C++ -*-

/*
 * PointArray.cpp
 *
 * HW 02, Point Class
 *
 */

#include <cstdlib>
#include <iostream>
#include <iostream>
#include <fstream>
#include <math.h>
#include "Point.cpp"

using namespace std;

class PointArray {

private: 
  Point** thePoints;
  int nElems;
  int appendIndex;

public:

  /*
   *Constructor needs to know up front the maximum size of the array.
   */ 
  PointArray(int numPoints) {
    thePoints = (Point**) calloc(numPoints, sizeof(Point*));
    nElems = numPoints;
    appendIndex = 0;
  }

  /* 
   * Since the constructor explicitly allocates an array of Points
   * dynamically, you should explicitly delete this array.
   */
  ~PointArray() {
    delete [] thePoints;
  }

  /*
   * Returns an exact clone of the array.
   */
  PointArray *copy() {
    PointArray *clone = new PointArray(nElems);
    for (int i = 0; i < nElems; i++) {
      clone->append(thePoints[i]);
    }
    return clone;
  }

  /*
   * Adds a new point to the array at the end
   */
  void append(Point *newPoint) {
    if (nElems == appendIndex) {
          std::cout << "Array has reached maximum size of " << nElems 
		    << ". Cannot add more elements\n";
	  exit(0);
    }

    thePoints[appendIndex] = newPoint;
    appendIndex++;
  }

  /* 
   * Adds a new point (x, y) to the end of the array
   */
  void append(int x, int y) {
    append(new Point(x, y));
  }

  /*
   * Adds a new point to location i
   */
  void insert(int i, Point *newPoint) {
    if (i >= nElems) {
      std::cout << "Cannot insert beyond maximum location " << nElems-1;
	  exit(0);
    }

    thePoints[i] = newPoint;
  }

  /* 
   * Adds a new point (x, y) to the location i
   */
  void insert(int i, int x, int y) {
    insert(i, new Point(x, y));
  }

  /* 
   * Returns a pointer to the point at index i
   */
  Point *getPoint(int i) {
    return thePoints[i];
  }

  /*
   * Allocated size of the array
   */
  int size() {
    return nElems;
  }

  /*
   * Sorts your array by X values in place by calling standard library
   * implementation of quicksort.
   */
  void sortByX() {
    qsort (thePoints, nElems, sizeof(Point *), Point::compareX);
  }

  /*
   * Sorts your array by Y values in place by calling standard library
   * implementation of quicksort.
   */
  void sortByY() {
    qsort (thePoints, nElems, sizeof(Point *), Point::compareY);
  }

  void print() {

    std::cout << "Pairs =  ";

    for (int i = 0; i < nElems - 1; i++) {
      thePoints[i]->print();
      std::cout << ", ";
    }
    thePoints[nElems - 1]->print();
    std::cout << std::endl;
  }

  // Prints the index of each point
  void print2() {

    std::cout << "Pairs =  ";

    for (int i = 0; i < nElems - 1; i++) {
      thePoints[i]->print2();
      std::cout << ", ";
    }
    thePoints[nElems - 1]->print2();
    std::cout << std::endl;
  }

};
