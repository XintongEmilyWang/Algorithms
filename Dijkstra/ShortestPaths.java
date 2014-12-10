import java.util.ArrayList;
/**
 * LAB 3b redo
 * @author Xintong Wang
 *
 */

//
// SHORTESTPATHS.JAVA
// Compute shortest paths in a graph.
//
// Your constructor should compute the actual shortest paths and
// maintain all the information needed to reconstruct them.  The
// returnPath() function should use this information to return the
// appropriate path of edge ID's from the start to the given end.
//
// Note that the start and end ID's should be mapped to vertices using
// the graph's get() function.
//
// You can ignore the input and startTime arguments to the constructor
// unless you are doing the extra credit.
//
class ShortestPaths {
	
	private Edge edges[];
	private int stId;
	private int dist[];
	private final static int INITIAL=1000000000;
    //
    // constructor
    //
    public ShortestPaths(Multigraph G, int startId, 
			 Input input, int startTime) 
    {
    	edges=new Edge[G.nVertices()];//create an array to store future edge values
    	stId=startId;
    	dist=new int[G.nVertices()];
    	Handle h[]=new Handle[G.nVertices()];
    	PriorityQueue<Vertex> pq=new PriorityQueue<Vertex>();//priority queue of vertices
    	//initialize all the vertices in the pq
    	for (int i=0;i<G.nVertices();i++){
    		dist[i]=INITIAL;
    		h[i]=pq.insert(INITIAL, G.get(i));   		
    	}
    	//initialize the source/starting point,decrease its key to zero;
    	dist[startId]=0;
    	pq.decreaseKey(h[startId], 0);
    	//Dijkstra's algorithm
    	while(pq.isEmpty()==false){
    		Vertex v=pq.extractMin();//always extract the smallest node
    		Vertex.EdgeIterator t=v.adj();//iterator through all the edges of the vertex;
    		while(t.hasNext()){//if t doesn't have next, stop the inner loop and extract min again
    			Edge e=t.next();
    			Vertex neighbor=e.to();
    			if(dist[v.id()]+e.weight()<dist[neighbor.id()]){
    				dist[neighbor.id()]=dist[v.id()]+e.weight();//relaxation step
    				pq.decreaseKey(h[neighbor.id()],dist[neighbor.id()]);//decrease the neighbor's key to the newkey got from its source node and the weighted edge
    				edges[neighbor.id()]=e;
    			}
    		}
    	}
    }
    
    //
    // returnPath()
    // Return an array containing a list of edge ID's forming
    // a shortest path from the start vertex to the specified
    // end vertex.
    //
    public int [] returnPath(int endId) 
    { 
	// your code here
    	ArrayList<Integer> list=new ArrayList<Integer>();//list to track the route
    	
    	while (endId!=stId){
    		list.add(edges[endId].id());//add new edge before the exist edge in the list
    		endId=edges[endId].from().id();//keep the loop until the endID is the start id
    	}

    	
	int empty[] = new int [list.size()];
	for (int i=0;i<list.size();i++){
		empty[i]=list.get(list.size()-1-i);//move element in the list to the empty array in the reverse order
	}
	return empty;//return the array as from the starting point to the destination
    }
    
}
