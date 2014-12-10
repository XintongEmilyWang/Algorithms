
public class Cell<T> {
	public int key;
	public T value;
	public Handle h;
	private final static int INF = (int)java.lang.Double.POSITIVE_INFINITY;
	
	public Cell(T v, int index){
		key=INF;//set key to a large value in order to decreasekey in future
		value=v;
		h=new Handle(key,false,index);
	}

}
