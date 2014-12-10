// -*- C++ -*-

/*
 * PointSupport.cpp
 *
 * Keeping the students distanced from the ugly.
 *
 */

#include <cstdlib>
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

/* 
 * This is how we read the points in from a file.
 * You should not need to modify this method. You
 * probably don't even need to understand it.
 */ 
PointArray *getPointsFromFile(char* filename) {

  PointArray *points;
  string line;
  int numPoints = 0;

  ifstream myfile (filename);
  if (myfile.is_open())
    {
      int i = 0;

      if (myfile.good()) {
	getline (myfile,line);
	numPoints = atoi(line.c_str());
	points = new PointArray(numPoints);
	std::cout << "File " << filename << " has : "
		  << numPoints << " points." << std::endl << std::endl;
      } 
      
      for (int i = 0; i < numPoints && myfile.good(); i ++) {
	
	int num;
	getline (myfile,line);
	std::stringstream ss(line);
	ss >> num;
	double x = (double)num;
	
	// ignore the comma
	ss.ignore();
	ss >> num;
	double y = (double)num;
	points->append(new Point(x, y, i));
      }
      myfile.close();
    }
  else {
    cout << "Unable to open file" << std::endl; 
    exit(0);
  }

  return points;
}

/* 
 * Returns a pointer to an array with a length of numPoints populated
 * with randomly generated points.
 */
PointArray *randomlyGeneratePoints(int numPoints) {
	PointArray *points;
 	points = new PointArray(numPoints);

 	srand(6712);

	std::cout << "Randomly generating " << numPoints << " points." << std::endl;

 	int x = 0;
 	int y = 0;

 	for (unsigned int i = 0; i < numPoints; ++i) {
 		x = rand() % (numPoints * 10);
 		y = rand() % (numPoints * 10);
 		points->append(new Point(x, y, i));
 	}

 	return points;
}
