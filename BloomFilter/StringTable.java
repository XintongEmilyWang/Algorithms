/**
 * hash table
 * @author Xintong Wang 
 * CSE 241
 */

// STRINGTABLE.JAVA
// A hash table mapping Strings to their positions in the the pattern sequence
// You get to fill in the methods for this part.
//
public class StringTable {
    private static final double LOADFACTOR=0.25;
    private static final Record DELETE=new Record(""); 
    private Record[] table;
    private int num;

    //
    // Create an empty table big enough to hold maxSize records.
    //
    public StringTable(int maxSize) 
    {
    	num=0;
    	table=new Record[maxSize];
    }
    //
    //Initialize the hash table to hold only 2 records 
    public StringTable() 
    {
    	this(2);
    }
    
    //
    // Insert a Record r into the table.  Return true if
    // successful, false if the table is full.  You shouldn't ever
    // get two insertions with the same key value, but you may
    // simply return false if this happens.
    //
    public boolean insert(Record r) 
    {   //first need to check whether the table is full already
    	if((double)(num/table.length)>LOADFACTOR){//if the table is full double its size
    		doubleTableSize();
    	}

    	int convert=toHashKey(r.key);
    	int i=baseHash(convert) % table.length;
    	int j=0;
    	/**if (find(r.key)!=null){//if the key is already in the table, do not insert and return false
    		return false;
    	}
    	else{**/
    		while(j<table.length){
    			if(table[i]==null||table[i]==DELETE){
    				table[i]=r;
    				table[i].hashValue=convert;//also assign the convert value to the records' hash value for the sake of future comparison
    				num++;
    				return true;
    			}
    			else{//if the slot already has a record, use the step hash function to find the next slot

    				i=(i+stepHash(convert)) % table.length;
    			}
    			j++;
    		}

    		return false; 
    	}
    //}
    
    //doubling the size of the table and rehashing and reinserting the records according to the new table length 
    public void doubleTableSize(){
    	num=0;
    	Record[]T=table;
    	table=new Record[T.length*2];
    	for(int i=0;i<table.length;i++){
    		if(T[i]!=null){
    			insert(T[i]);//reinsert the record according to the new table length
    		}
    	}
    }
    
    
    //
    // Delete a Record r from the table.  Note that you'll have to
    // find the record first unless you keep some extra information
    // in the Record structure.
    //
    public void remove(Record r) 
    {
    	int convert=toHashKey(r.key);
    	int i=baseHash(convert) % table.length;
    	
    	while (table[i]!=null){
    		//when finding the record, first check whether the hash value of the two record
    		//match. If it does not match, we can avoid the full comparison of the two strings 
    		if(table[i].hashValue==convert && table[i].key.equals(r.key)){
    			table[i]=DELETE;
    			num--;
    			return;
    		}
    		else{//if the key does not match to table"i", go on finding other slots
    			i=(i+stepHash(convert)) % table.length;
    		}
    	}
    }
    
    
    //
    // Find a record with a key matching the input.  Return the
    // record if it exists, or null if no matching record is found.
    //
    public Record find(String key) 
    {
    	int convert=toHashKey(key);
    	int i=baseHash(convert) % table.length;
    	
    	while(table[i]!=null){
    		//when finding the record, first check whether the hash value of the two record
    		//match. If it does not match, we can avoid the full comparison of the two strings 
    		if (table[i].hashValue==convert && table[i].key.equals(key)){
    			return table[i];
    		}
    		else{//if the key does not match to table"i", go on finding other slots
    			i=(i+stepHash(convert)) % table.length;
    		}
    	}
    	return null; 
    }
    
    
    ///////////////////////////////////////////////////////////////////////
    
    
    // Convert a String key into an integer that serves as input to hash
    // functions.  This mapping is based on the idea of a linear-congruential
    // pesudorandom number generator, in which successive values r_i are 
    // generated by computing
    //    r_i = ( A * r_(i-1) + B ) mod M
    // A is a large prime number, while B is a small increment thrown in
    // so that we don't just compute successive powers of A mod M.
    //
    // We modify the above generator by perturbing each r_i, adding in
    // the ith character of the string and its offset, to alter the
    // pseudorandom sequence.
    //
    int toHashKey(String s)
    {
	int A = 1952786893;
	int B = 367257;
	int v = B;
	
	for (int j = 0; j < s.length(); j++)
	    {
		char c = s.charAt(j);
		v = A * (v + (int) c + j) + B;
	    }
	
	if (v < 0) v = -v;
	return v;
    }
    
    // Fill in your own hash function here
    int baseHash(int hashKey)
    {
    	double A=(Math.sqrt(5)-1)/2;
    	return (int)(((double)A*hashKey-(int)(A*hashKey))* table.length);
    }
    
 // Fill in your own hash function here
    int stepHash(int hashKey)
    {
    	if (table.length>2){
    		return 1+2*(hashKey % ((int)(table.length/3)+1));
    	}
    	else
    		return 1;//if the table length is just 2, simply plus one to the base hash
    }
}

