// -*- C++ -*-

/*
 * Point.cpp
 *
 * HW 02, Point Class
 *
 */

#pragma once

#include <cstdlib>
#include <iostream>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

class Point 
{

private: 
  double x, y;
  int index;

public:
  
  Point() {
    x = 0.0;
    y = 0.0;
    index=0;
  }

  Point(double xVal, double yVal) {
    x = xVal;
    y = yVal;
    index = 0;
  }

  Point(double xVal, double yVal, int i) {
    x = xVal;
    y = yVal;
    index = i;
  }


  /* 
   * Returns the Euclidian distance from this point to the other point
   */
  double distance(Point *other) {
    double xd = x - other->getX();
    double yd = y - other->getY();

    return sqrt (xd*xd + yd*yd);
  }

  int getX() {
    return x;
  }

  int getY() {
    return y;
  }

  int getIndex(){
    return index;
  }

  void print() {
    std::cout << "(" << (int)x << "," << (int)y << ")";
  }
  
  void print2() {
    std::cout << "(" << (int)x << "," << (int)y << ")["<< index << "]";
  }
  
  /* 
   * Static function that compares two Points by comparing their x values.
   */ 
  static int compareX(const void *a, const void *b) {

    Point *p1 = *(Point **)a;
    Point *p2 = *(Point **)b;

    if (p1->getX() == p2->getX()){
      if (p1->getY() == p2->getY()) 
	return (p1->getIndex() - p2->getIndex());
      else return (p1->getY() - p2->getY());
    }
    return (p1->getX() - p2->getX());
  }

  /* 
   * Static function that compares two Points by comparing their y values.
   */ 
  static int compareY(const void *a, const void *b) {

    Point *p1 = *(Point **)a;
    Point *p2 = *(Point **)b;

    if (p1->getY() == p2->getY()){
      if (p1->getX() == p2->getX())
	return (p1->getIndex() - p2->getIndex());
      else return (p1->getX() - p2->getX());
    }

    return (p1->getY() - p2->getY());
  }


 
};
