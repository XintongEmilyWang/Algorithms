public class Handle<T> {
	public int key;
	public boolean exist;//the state of the cell
	public int index;
	
	public Handle(int k,boolean tf,int i){
		key=k;
		exist=tf;//exist can be true or false to differentiate the removed cell
		index=i;		
	}
}
