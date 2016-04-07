package correction.tp3.pile;

import java.util.ArrayList;
import java.util.List;

public class ArrayStack implements Stack {
	
	private List<Object> array = new ArrayList<Object>();
	private int indice =0;
	
	@Override
	public boolean isEmpty() {
		// TODO Auto-generated method stub
		return this.array.isEmpty();
	}

	@Override
	public Object pop() {
		Object o = null;
		// TODO Auto-generated method stub
		if(this.array.isEmpty()){
			return null;
		}else{
			this.indice = this.indice - 1;
			o = this.array.remove(indice);
			return o;
		}
	}

	@Override
	public void push(Object o) {
		// TODO Auto-generated method stub
		this.array.add(indice, o);
		indice++;
	}

	@Override
	public Object top() {
		// TODO Auto-generated method stub
		if(this.array.isEmpty()){
			return null;
		}else{
			int i = indice--;
			return this.array.get(i);
		}
	}
	
	@Override
	public String toString() {
		// TODO Auto-generated method stub
		return "Array:"+this.array.toString();
	}

}
