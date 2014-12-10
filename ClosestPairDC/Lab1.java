//
// LAB1.JAVA
// Main driver code for CSE 241 Lab #1.
//

import java.util.*;

public class Lab1 {
    
    static final long seed = 5498;
    
    public static void main(String args[])
    {
	XYPoint points [];
	String fileName;
	
	if (args.length >= 1)
	    {
		fileName = args[0];
	    }
	else
	    {
		System.out.println("Syntax: Lab1 <filename>");
		return;
	    }
			
	
	// A filename argument of the form '@x', where x is a non-negative
	// integer, allocates x random points.  Any other argument is
	// assumed to be a file from which points are read.
	
	if (fileName.charAt(0) != '@')
	    {
		points = PointReader.readXYPoints(fileName);
	    }
	else
	    {
		int nPoints = Integer.parseInt(fileName.substring(1));
		
		PRNG prng = new PRNG(seed);
		
		points = genPointsAtRandom(nPoints, prng);
	    }
	
	if (points.length < 2)
	    {
		System.out.println("ERROR: input must contain at least two points");
		return;
	    }
	
	{
	    XComparator lessThanX = new XComparator();
	    YComparator lessThanY = new YComparator();
	    
	    Date startTime = new Date();
	    
	    /////////////////////////////////////////////////////////////////
	    // CLOSEST-PAIR ALGORITHM STARTS HERE	
	    
	    // The algorithm expects two arrays containing the same points.
	    XYPoint pointsByX [] = new XYPoint [points.length];
	    XYPoint pointsByY [] = new XYPoint [points.length];
	    
	    for (int j = 0; j < points.length; j++)
		{
		    pointsByX[j] = points[j];
		    pointsByY[j] = points[j];
		}
	    
	    // Ensure sorting precondition for divide-and-conquer CP
	    // algorithm.  NB: you should *not* have to call sort() in
	    // your own code!
	    
	    Arrays.sort(pointsByX, lessThanX); // sort by x-coord
	    Arrays.sort(pointsByY, lessThanY); // sort by y-coord
	    
	    ClosestPairDC.findClosestPair(pointsByX, pointsByY);
	    
	    // CLOSEST-PAIR ALGORITHM ENDS HERE
	    /////////////////////////////////////////////////////////////////
	    
	    Date endTime = new Date();
	    long elapsedTime = endTime.getTime() - startTime.getTime();
	    
	    System.out.println("For n = " + points.length + 
			     ", the elapsed time is " +
			     elapsedTime + " milliseconds.");
	    System.out.println("");
	}
	
	
	// Now run the naive algorithm
	{
	    Date startTime = new Date();
	    
	    ClosestPairNaive.findClosestPair(points);
	    
	    Date endTime = new Date();
	    long elapsedTime = endTime.getTime() - startTime.getTime();
	    
	    System.out.println("For n = " + points.length + 
			     ", the naive elapsed time is " +
			     elapsedTime + " milliseconds.");
	    System.out.println("");
	}
	
	// *** NOTE: for your submitted output, you MUST print the
	// *** closest pair of points and the distance between them!
    }
    
    
    //
    // genPointsAtRandom()
    // Generate an array of specified size containing
    // points with coordinates chosen at random, using
    // the specified random sequence generator.
    //
    
    static XYPoint[] genPointsAtRandom(int nPoints, 
				       PRNG prng) 
    {
	XYPoint points[] = new XYPoint [nPoints];
	
	double x = 0.0;
	double y = 0.0;
	
	double step = Math.sqrt(nPoints);
	
	for (int j = 0; j < nPoints; j++) 
	    {
		// jitter next point's X coordinate
		x += 10000.0 * (prng.nextDouble() - 0.5);
		
		// move the Y coordinate a random amount up,
		// while keeping it within limits [0 .. nPoints)
		y = (y + step * prng.nextDouble()) % nPoints;
		
		points[j] = new XYPoint((int) Math.round(x), 
					(int) Math.round(y));
	    }
	
	return points;
    }
}
