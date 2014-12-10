// -*- C++ -*-

/*
 * ClosestPair.cpp
 *
 * HW 02, cilk version from the original closestPair.sml at CMU
 *
 */

#include <cstdlib>
#include <cilk/cilk.h>
#include <cilk/reducer_min.h>
#include <iostream>
#include <iostream>
#include <fstream>
#include <limits>
#include "PointArray.cpp"
#include "PointSupport.cpp"
#include "PairResult.cpp"
#include "StudentSolution2.cpp"
#include "Timer.cpp"

using namespace std;

// DO NOT MODIFY THIS FILE !!!!
// (the Auto-Grader will use the original version of this file,
// so any modifications you make here will be discarded before
// your assignment is graded)

#define MAX_FOR_QUADRATIC 10000

int defaultNumPoints = 10;
bool printPoints_f = false;
bool printResult_f = true;

int pairMain(int numPoints, char* myFile)
{
  
  PointArray *xPoints;
  bool executeQuadratic_f = true;
  
  std::cout << "------------------------------------------------\n"
	    << "CLOSEST PAIR PROBLEM: Given a sequence of points\n"
	    << "S = ⟨p1, . . . , pn⟩, where pi = (xi, yi), report \n"
	    << "the distance between the closest pair of points.\n"
	    << "------------------------------------------------\n";
  
  // Initialize Point array
  if (myFile != NULL) {
    // get the points from the input file
    xPoints = getPointsFromFile(myFile);
  }
  else {
    // get random points
    xPoints = randomlyGeneratePoints(numPoints);
  }
  
  executeQuadratic_f = (numPoints <= MAX_FOR_QUADRATIC);
  // don't print a really long sequence. that's madness
  printPoints_f = printPoints_f && executeQuadratic_f;
  if (printPoints_f)
    xPoints->print();
  
  Timer *bruteTimer = new Timer(new string("Brute Force (Quadratic)"));
  Timer *recTimer = new Timer(new string("Recursive (Serial)"));
  Timer *recParTimer = new Timer(new string("Recursive Parallel"));

  PairResult *recResult = new PairResult();
  PairResult *recParResult = new PairResult();

  if (executeQuadratic_f) {
    PairResult *bruteResult = new PairResult();

    bruteTimer->printBegin();
    bruteTimer->begin();
    solveClosestPairBrute(xPoints, bruteResult);
    bruteTimer->end();

    if (printResult_f)
      bruteResult->print();

    bruteTimer->print();
  }
  else {
    std::cout << "Brute force method not running, too many points" << endl << endl;
  }

  // Now we need two arrays, one sorted by X and one by Y
  PointArray *yPoints = xPoints->copy();

  xPoints->sortByX();
  yPoints->sortByY();

  // Recursive Serial
  recTimer->printBegin();
  recTimer->begin();
  solveClosestPairRecurse(xPoints, 0, xPoints->size(), yPoints, 0, yPoints->size(), recResult);
  recTimer->end();

  if (printResult_f)
    recResult->print();

  recTimer->print();
  if (executeQuadratic_f)
    recTimer->printSpeedup(bruteTimer);
  
  // Recursive Parallel
  recParTimer->printBegin();
  recParTimer->begin();
  solveClosestPairParallel(xPoints, 0, xPoints->size(), yPoints, 0, yPoints->size(), recParResult);
  recParTimer->end();

  if (printResult_f)
    recParResult->print();

  recParTimer->print();

  if (executeQuadratic_f)
    recParTimer->printSpeedup(bruteTimer);
  recParTimer->printSpeedup(recTimer);

  xPoints->~PointArray();
  yPoints->~PointArray();
  return 0;
}

int main(int argc, char* argv[])
{
  int numPoints = defaultNumPoints;
  char *myFile = NULL;
  if (argc > 1) {
    // they might just be asking for usage information
    if (std::string(argv[1]) == "-help") {
	std::cout << "--------- ClosestPair -help -------------------" << std::endl;
	std::cout << "Usage: ./ClosestPair -f filename -pPts 1" << std::endl 
		  << "        --OR--" << std::endl 
		  << "       ./ClosestPair -n 30" << std::endl 
		  << "       where: " << std::endl 
		  << " -f filename specifies a file called filename with the pairs in it" << std::endl
		  << "             First line of the file gives number of pairs" << std::endl
		  << "             Each line after that gives an x or y value" << std::endl
		  << " -pPts 1|0   whether you want the Points to be printed (Default = 0)" << std::endl
		  << " -pSol 1|0   whether you want the solution to be printed (Default = 1)" << std::endl
		  << " The following arguments apply ONLY to randomly generated stock sequences:" << std::endl
		  << "             (which will occur if no input file is specified)" << std::endl
		  << " -n x        limits number of Points to x (Default = " << defaultNumPoints << ")" << std::endl;
	exit(0);
    }
    
    // or they might actually want to run the code!
    for (int i = 1; i < argc; i=i+2) {
      if (std::string(argv[i]) == "-f") {
	// We know the next argument *should* be the filename:
        myFile = argv[i + 1];
      } else if (std::string(argv[i]) == "-n") {
	// We know the next argument *should* be number of Points:
	numPoints = atoi(argv[i + 1]);
      } else if (std::string(argv[i]) == "-pPts") {
	// We know the next argument *should* be 1 or 0
	printPoints_f = (atoi(argv[i + 1]) == 0) ? false : true;
      } else if (std::string(argv[i]) == "-pRes") {
	// We know the next argument *should* be 1 or 0
	printResult_f = (atoi(argv[i + 1]) == 0) ? false : true;
      } 
    }
  }
  std::cout << "Note: for a complete explanation of command line arguments, type: ./ClosestPair -help" << std::endl;

  return pairMain(numPoints, myFile);

}
