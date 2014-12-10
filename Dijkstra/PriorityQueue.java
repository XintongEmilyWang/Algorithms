import java.util.ArrayList;
/**
 * Lab redo
 * @author Xintong Wang
 * 418999
 * @param <T>
 */

//
// PRIORITYQUEUE.JAVA
// A priority queue class supporting sundry operations needed for
// Dijkstra's algorithm.
//

class PriorityQueue<T> {

	public ArrayList<Cell<T>> list;
	public int size;
	private int capacity;

	// constructor
	// create an empty queue
	public PriorityQueue()
	{
		list=new ArrayList<Cell<T>>();
		size=0;
		capacity=15;//4 level heap
	}

	// Return true iff the queue is empty.
	//
	public boolean isEmpty()
	{
		return(size==0);
	}

	// Insert a pair (key, value) into the queue, and return
	// a Handle to this pair so that we can find it later in
	// constant time.
	//

	Handle insert(int key, T value)
	{
		Cell<T> c=new Cell<T> (value,size);
		list.add(c);//add the new node to the array list
		Handle h=c.h;
		c.h.exist=true;//update the state of cell
		decreaseKey(h, key);
		size++;//keep track of the size of the list
		if(size==capacity){
			capacity=2*capacity;//if size reaches its capacity, double the list's capacity
		}
		return h;
	}

	// Return the smallest key in the queue.
	//
	public int min()
	{
		if(isEmpty());
		// throw string("the heap is empty");
		return list.get(0).key;//the upper node in the heap
	}

	/**
	 * swap two cells when there is a violation in the heap, keep all the properties of the cell unchanged except index
	 * @param a
	 * @param b
	 */
	private void swap(Cell<T> a,Cell<T> b){
		int i=a.h.index;
		int j=b.h.index;//record the two index numbers of the two cells need exchange
		list.set(i, b);
		b.h.index=i;//update the index
		list.set(j, a);
		a.h.index=j;//update the index
	}


	// Extract the (key, value) pair associated with the smallest
	// key in the queue and return its "value" object.
	//
	public T extractMin()
	{
		T value=list.get(0).value;
		swap(list.get(0), list.get(size-1));//exchange the last node with the min
		list.get(size-1).h.exist=false;//set the removed cell's status to false, not exist;
		list.remove(size-1);//extract min
		size--;//keep track of the size of the list
		int i=0;
		while(2*i+1<size){//loop until a child reaches the size of the array list
			Cell<T> leftChild=list.get(2*i+1);//index starts from 0
			if(size==2*i+2){
				if(leftChild.key<list.get(i).key){//the parent only has a left child
					swap(list.get(i),list.get(2*i+1));
				}
				break;
			}

			Cell<T> rightChild=list.get(2*i+2);	//right child
			int track=2*i+1;//starting from the left child
			if(leftChild.key>rightChild.key) 	//left child greater than right child
				track++;//when left child is larger than right child, move the comparison tracker to the right child
			if(list.get(track).key<list.get(i).key){
				swap(list.get(i),list.get(track));	
				i=track;//move i to the already swapped position and start the loop again
			}
			else break;	//parent is smaller than child
		}
		return value;
	}


	// Look at the (key, value) pair referenced by Handle h.
	// If that pair is no longer in the queue, or its key
	// is <= newkey, do nothing and return false.  Otherwise,
	// replace "key" by "newkey", fixup the queue, and return
	// true.
	//

	public boolean decreaseKey(Handle h, int newkey)
	{	
		if(h.exist==false||list.get(h.index).key<=newkey){//when the cell has been removed or the original key is smaller than the new key
			return false;//do nothing
		}
		else{
			list.get(h.index).key = newkey;
			while(h.index>0&&list.get(h.index).key<list.get((h.index-1)/2).key){//if the node's parent is larger, swap the two nodes
				swap(list.get(h.index), list.get((h.index-1)/2));
			}
			return true;
		}
	}


	// Get the key of the (key, value) pair associated with a 
	// given Handle. (This result is undefined if the handle no longer
	// refers to a pair in the queue.)
	//

	public int handleGetKey(Handle h)
	{
		if(h.exist==false)//when the cell has been removed
			;
		return list.get(h.index).key;
	}

	// Get the value object of the (key, value) pair associated with a 
	// given Handle. (This result is undefined if the handle no longer
	// refers to a pair in the queue.)
	//
	public T handleGetValue(Handle h)
	{
		if(h.exist){
		return list.get(h.index).value;
		}
		else{
			return null;
		}
	}

	// Print every element of the queue in the order in which it appears
	// in the implementation (i.e. the array representing the heap).

	public String toString()
	{
		String s = "";
		for (int i=0;i<size;i++){
			s =s+ "("+list.get(i).key+","+list.get(i).value+")";
		}
		return s;
	}
}
