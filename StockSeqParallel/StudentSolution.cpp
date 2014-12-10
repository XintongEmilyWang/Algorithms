// -*- C++ -*-

/*
 * StudentSolution.cpp
 *
 * HW 01, cilk version from the original stocks.sml at CMU
 *
 * THIS is the only file we will look at when we grade your homework.
 * All other changes you made to any other files will be discarded.
 */

#include <cstdlib>
#include <cilk/cilk.h>
#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define MIN(x, y) ((x < y) ? x : y)
#define MAX(x, y) ((x > y) ? x : y)

// YOUR naive, quadratic stock market algorithm
void solveStocksNaive(const vector<int> &stockSequence, int beginIndex, int seqLength, StocksResult *result)
{
  result->jump=0;
  for(int i=0;i<seqLength-1;i++){
    for(int j=i+1;j<seqLength;j++){
      if(stockSequence[j]-stockSequence[i]>result->jump){
	result->jump=stockSequence[j]-stockSequence[i];
	result->bestSell=stockSequence[j];
	result->bestBuy=stockSequence[i];
      }
    }
  }
}

// YOUR recursive, divide and conqure stock market algorithm
void solveStocksRecurse(const vector<int> &stockSequence, int beginIndex, int seqLength, StocksResult *result)
{//base case
  if(seqLength<2){
    result->jump=0;
    result->low=stockSequence[beginIndex];
    result->high=stockSequence[beginIndex];
    return;
  }
  else{
  //divide and conquer
    StocksResult *leftRes=new StocksResult();
    StocksResult *rightRes=new StocksResult();
    int divLength=seqLength/2;

    solveStocksRecurse(stockSequence,beginIndex,divLength,leftRes);
    solveStocksRecurse(stockSequence,beginIndex+divLength,seqLength-divLength,rightRes);
    //combine
    int across=rightRes->high-leftRes->low;
    result->jump=MAX(MAX(rightRes->jump,leftRes->jump),across);
    result->low=(leftRes->low<rightRes->low?leftRes->low:rightRes->low);
    result->high=(leftRes->high>rightRes->high?leftRes->high:rightRes->high);
    result->bestSell=(result->jump==across?rightRes->high:(result->jump==leftRes->jump?leftRes->bestSell:rightRes->bestSell));
    result->bestBuy=(result->jump==across?leftRes->low:(result->jump==leftRes->jump?leftRes->bestBuy:rightRes->bestBuy));

    delete leftRes;
    delete rightRes;
  }
}

// YOUR recursive, divide and conqure stock market algorithm
void solveStocksRecPar(const vector<int> &stockSequence, int beginIndex, int seqLength, StocksResult *result)
{//base case
  if(seqLength<2){
    result->jump=0;
    result->low=stockSequence[beginIndex];
    result->high=stockSequence[beginIndex];
    return;
  }
  else{
  //divide and conquer
    StocksResult *leftRes=new StocksResult();
    StocksResult *rightRes=new StocksResult();
    int divLength=seqLength/2;
    cilk_spawn solveStocksRecPar(stockSequence,beginIndex,divLength,leftRes);
    cilk_spawn solveStocksRecPar(stockSequence,beginIndex+divLength,seqLength-divLength,rightRes);
    cilk_sync;

    //combine
    int across=rightRes->high-leftRes->low;
    result->jump=MAX(across,MAX(rightRes->jump,leftRes->jump));
    result->low=(leftRes->low<rightRes->low?leftRes->low:rightRes->low);
    result->high=(leftRes->high>rightRes->high?leftRes->high:rightRes->high);
    result->bestSell=(result->jump==across?rightRes->high:(result->jump==leftRes->jump?leftRes->bestSell:rightRes->bestSell));
    result->bestBuy=(result->jump==across?leftRes->low:(result->jump==leftRes->jump?leftRes->bestBuy:rightRes->bestBuy));

    delete leftRes;
    delete rightRes;
  }

}
