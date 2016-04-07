package correction.tp2.utiliteClasseAbstraite;

import java.util.AbstractList;
import java.util.Spliterator;

public class MyListEntier extends AbstractList<Integer>{
	
	private static final int SIZE = 10;
	
	private Integer[] tab;
	
	private int index;
	
	public MyListEntier(){
		super();
		
		this.index = SIZE;
		this.tab = new Integer[SIZE];
	}

	@Override
	public boolean add(Integer e){
		if(index < SIZE){
			tab[index] = e;
			index++;
			return true;
		}else{
			return false;
		}
	}

	@Override
	public Integer get(int index) {
		if(index < SIZE && index > -1){
			return tab[index];
		}else{
			throw new IndexOutOfBoundsException();
		}
	}

	@Override
	public int size() {
		return SIZE;
	}
	
	@Override
	public Spliterator<Integer> spliterator() {
		return null;
	}
	
}
