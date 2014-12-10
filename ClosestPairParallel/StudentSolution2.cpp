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
#include <fstream>
#include <limits>
#include <vector>
#include <cilk/reducer_opadd.h>

using namespace std;

const double INF=numeric_limits<double>::infinity();
/* 
 * This method implements the brute force method of finding closest points.
 * Use this to test the correctness of the recursive O(nlogn) method on small sets.
 * The points don't need to be sorted
 */

void solveClosestPairBrute(PointArray *points, PairResult *result) {
  int nPoints=points->size();
  //initialize
  result->pointOne=0;
  result->pointTwo=0;
  result->distance=INF;

  if(nPoints==1){
    result->pointOne=points->getPoint(0);
    result->pointTwo=0;
    result->distance=INF;
  }else{
    for(int i=0;i<nPoints-1;i++){
      for(int j=i+1;j<nPoints;j++){
	Point *one=points->getPoint(i);
	Point *two=points->getPoint(j);
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
 *   (1) divide -- split the input sequence in approximately half 
 *   (2) recurse -- recursively solve the two halves of the problem
 *   (3) combine -- find the solution to your input
 * The two arrays xPoints and yPoints are already sorted by x and y respectively.
 * The range of each array is (begin, end] (inclusive of begin, exclusive of end]
 */
void boundedDivide(Point **pointsByY, int mid, Point *midPoint, int first, int last) {
    int a=0,b=mid-first+1;
    Point **temp=new Point* [last-first+1];
    for(int i=first;i<=last;i++){

      if(pointsByY[i]->getX()-midPoint->getX()<0){
            temp[a++]=pointsByY[i];
      } 
      else if(pointsByY[i]->getX()-midPoint->getX()>0){
            temp[b++] = pointsByY[i];
      } 
      else if (pointsByY[i]->getX()==midPoint->getX()
	       &&pointsByY[i]->getY()<=midPoint->getY()){
            temp[a++] = pointsByY[i];
      }
 
      else {
            temp[b++] = pointsByY[i];
      }
    }

    for(int i=first;i<=last;i++){
        pointsByY[i]=temp[i-first];
    }
    //free temp
    delete [] temp;
}



void boundedDistance(Point **pointsByY, int length, Point *midPoint, PairResult *result) {
    int size=0;
    Point **inBound=new Point *[length];
    //combine
    for(int i=0;i<length;i++){
        if(abs(midPoint->getX()-pointsByY[i]->getX())<=result->distance){
          inBound[size++]=pointsByY[i];
        }
    }
    if(size>= 2){
        double dist=INF;
        for(int i=0;i<size;i++){
            int j= i+1;
            while(j<size&&inBound[j]->getY()-inBound[i]->getY()<=result->distance){
                dist=inBound[i]->distance(inBound[j]);
                if(dist<result->distance){
                    result->distance=dist;
                    result->pointOne=inBound[i];
                    result->pointTwo=inBound[j];
                }
                j++;
            }
        }
    }
    delete []inBound;
}



void solveClosestPairRecurseHelper(PointArray *pointsByX, Point **pointsByY, int first, int last, PairResult *result) {

    int nPoints=last-first+1;
    // Base
    if(nPoints<=1){
        return;
    }
    if(nPoints==2){
        double dist=pointsByX->getPoint(first)->distance(pointsByX->getPoint(last));
        if(dist<result->distance){
            result->pointOne=pointsByX->getPoint(first);
            result->pointTwo=pointsByX->getPoint(last);
            result->distance=dist;
        }
        return;
    }

    int pivot=first+(last-first)/2;
    Point *pivPoint=pointsByX->getPoint(pivot);
    Point **copy=new Point* [nPoints];
    for(int i=0;i<nPoints;i++){
        copy[i]=pointsByY[i+first];
    }
    //where recursion
    boundedDivide(pointsByY,pivot,pivPoint,first,last);
    solveClosestPairRecurseHelper(pointsByX,pointsByY,pivot+1,last,result); //right
    solveClosestPairRecurseHelper(pointsByX,pointsByY,first,pivot,result); //left
    boundedDistance(copy,nPoints,pivPoint,result);
    delete [] copy;
}


void solveClosestPairRecurse(PointArray *xPoints, int beginX, int endX, PointArray *yPoints, int beginY, int endY, PairResult *result) {
    result->distance=INF;
    int nPoints=endX-beginX;
    PointArray *points=xPoints;
    Point **pointsByY=new Point*[nPoints];
   
    for(int i=0;i<nPoints;i++) {
        pointsByY[i]=yPoints->getPoint(i);
    }

    solveClosestPairRecurseHelper(points,pointsByY,beginX,endX-1,result);
    delete [] pointsByY;
}

/* 
 * This is the parallel version of our recrusive method.
 */
//calc the prefix sum array
int *prefixSumParallel(int array[],int n){
    int *result=new int[n];
    if(n==1){
        result[0]=array[0];
        return result;
    }
    int split;
    int *t=0;
    if(n%2==0){
        split=n/2;
        t=new int[split];
        cilk_for(int i=0;i<split;i++){
            t[i]=array[2*i]+array[2*i+1];
        }
    } 
    else {
        split=n/2+1;
        t=new int[split];
        cilk_for(int i=0;i<split-1;i++){
           t[i]=array[2*i]+array[2*i+1];
        }
	t[split-1]=array[n-1];
    }

    int *temp=prefixSumParallel(t,split);
    delete [] t;
    //prefix sum for each elemetn
    cilk_for(int i=0;i<n;i++){
        if(i==0){
            result[0]=array[0];
        } 
	else if(i%2==1){
            result[i]=temp[i/2];
        } 
	else{
            result[i]=temp[i/2-1]+array[i];
        }
    }
    delete []temp;
    return result;
}


void boundedDivideParallel(Point **pointsByY, int mid, Point *midPoint, int first, int last) {

    Point **temp=new Point*[last-first+1];
    int *t=new int[last-first+1];
    int *prefixSumTemp=0;
    int *prefixSum=new int[last-first+1];

    cilk_for(int i=first;i<=last;i++){
        if(pointsByY[i]->getX()-midPoint->getX()<0||
        (pointsByY[i]->getX()==midPoint->getX()
	 &&pointsByY[i]->getY()<=midPoint->getY())){
            t[i-first]=1;
        }
	else{
            t[i-first]=0;
        }
    }
    // calc prefix sum
    prefixSumTemp=prefixSumParallel(t,last-first+1);
    prefixSum[0]=0;

    
    cilk_for(int i=1;i<last-first+1;i++){
        prefixSum[i]=prefixSumTemp[i-1];
    }

    cilk_for(int i=0;i<last-first+1;i++){
        if(t[i]==1){
            temp[prefixSum[i]]=pointsByY[i+first];    
        }
    }
    int total=prefixSumTemp[last-first];
    
    cilk_for(int i=first;i<=last;i++){
        if(pointsByY[i]->getX()-midPoint->getX()>0||
            (pointsByY[i]->getX()==midPoint->getX()
	     &&pointsByY[i]->getY() >midPoint->getY())) {
            t[i-first]=1;
        } else {
            t[i-first]=0;
        }
    }
   
    prefixSumTemp=prefixSumParallel(t,last-first+1);
    prefixSum[0]=0;
    
    cilk_for(int i=1;i<last-first+1;i++){
        prefixSum[i]=prefixSumTemp[i-1];
    }

    cilk_for(int i=0;i<last-first+1;i++){
        if(t[i]==1){
           temp[prefixSum[i]+total] = pointsByY[i+first];
        }
    }
    cilk_for(int i=first;i<=last;i++){//maintain the array
        pointsByY[i]=temp[i-first];
    }
    //free all temp
    delete []temp;
    delete []t;
    delete []prefixSumTemp;
    delete []prefixSum;
}



void boundedDistanceParallel(Point **pointsByY,int length,Point *midPoint,PairResult *result){
    int size=0;
    Point **inBound=new Point *[length];
    int *l=new int [length];
    int *temp=0;
    int *prefixSum=new int[length];
    cilk_for(int i=0;i<length;i++){
      if(abs(midPoint->getX()-pointsByY[i]->getX())<=result->distance){
            l[i] = 1;
      }
      else{
            l[i] = 0;
      }
    }

    temp=prefixSumParallel(l,length);
    prefixSum[0] = 0;

    cilk_for(int i=1;i<length;i++){
        prefixSum[i]=temp[i-1];
    }    

    cilk_for(int i=0;i<length;i++){
        if(l[i] == 1)
            inBound[prefixSum[i]]=pointsByY[i];
    }
    size=temp[length-1];
    delete [] temp;
    delete [] prefixSum; 
    delete [] l;

    if(size>= 2){
        double dist=INF;
        vector<PairResult> v;
        PairResult resultS;
        v.assign(size,resultS);
        cilk_for(int i=0;i<size;i++){
            int j= i+1;
            PairResult resultS;
            resultS.distance = INF;
            while(j<size&&inBound[j]->getY()-inBound[i]->getY()<=result->distance){
                dist=inBound[i]->distance(inBound[j]);
                if(dist<result->distance){
                    result->distance=dist;
                    result->pointOne=inBound[i];
                    result->pointTwo=inBound[j];
                }
                j++;
            }
	    v[i]=resultS;
        }

        cilk::reducer_min_index<size_t,double> reduce;
        cilk_for(size_t i=0;i<v.size();i++){
            reduce.min_of(i,v[i].distance);
        }
        size_t i=reduce.get_index();
        if(v[i].distance<result->distance){
            result->distance=v[i].distance;
            result->pointOne=v[i].pointOne;
            result->pointTwo=v[i].pointTwo;
        }
    }  
    delete []inBound;
}



void solveClosestPairParallelHelper(PointArray *pointsByX,Point **pointsByY,int first,int last,PairResult *result) {
    int nPoints=last-first+1;
    // Base
    if(nPoints<=1){
        return;
    }
    if(nPoints==2){
        double dist=pointsByX->getPoint(first)->distance(pointsByX->getPoint(last));
        if(dist<result->distance){
            result->pointOne=pointsByX->getPoint(first);
            result->pointTwo=pointsByX->getPoint(last);
            result->distance=dist;
        }
        return;
    }

    int pivot=first+(last-first)/2;
    Point *pivPoint=pointsByX->getPoint(pivot);
    Point **copy=new Point* [nPoints];
    cilk_for(int i=0;i<nPoints;i++){
        copy[i]=pointsByY[i+first];
    }

    boundedDivideParallel(pointsByY,pivot,pivPoint,first,last);
    cilk_spawn solveClosestPairParallelHelper(pointsByX,pointsByY,pivot+1,last,result); //right
    cilk_spawn solveClosestPairParallelHelper(pointsByX,pointsByY,first,pivot,result); //left
    cilk_sync;
    boundedDistanceParallel(copy,nPoints,pivPoint,result);
    delete [] copy;
}

void solveClosestPairParallel(PointArray *xPoints, int beginX, int endX, PointArray *yPoints, int beginY, int endY, PairResult *result) {
    result->distance=INF;
    int nPoints=endX-beginX;
    PointArray *points=xPoints;
    Point **pointsByY=new Point* [nPoints];
    cilk_for(int i=0;i<nPoints;i++){
        pointsByY[i]=yPoints->getPoint(i);
    }
    solveClosestPairParallelHelper(xPoints,pointsByY,beginX,endX-1,result);
    delete [] pointsByY;
}
