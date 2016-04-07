package correction.tp3.pile;

import java.util.Vector;
import java.util.List;

public class VectorStack implements Stack {
	
	private List<Object> list = new Vector<Object>();
	private int indice =0;
	
	@Override
	public boolean isEmpty() {
		// TODO Auto-generated method stub
		return list.isEmpty();
	}

	@Override
	public Object pop() {
		Object o = null;
		// TODO Auto-generated method stub
		if(this.list.isEmpty()){
			return null;
		}else{
			this.indice = this.indice - 1;
			o = this.list.remove(indice);
			return o;
		}
	}

	@Override
	public void push(Object o) {
		// TODO Auto-generated method stub
		this.list.add(indice, o);
		indice++;
	}

	@Override
	public Object top() {
		// TODO Auto-generated method stub
		if(this.list.isEmpty()){
			return null;
		}else{
			int i = indice--;
			return this.list.get(i);
		}
	}
	
	@Override
	public String toString() {
		// TODO Auto-generated method stub
		return "Vector:"+ this.list.toString();
	}

}