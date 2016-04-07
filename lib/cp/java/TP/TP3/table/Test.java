package correction.tp3.table;

import java.util.Iterator;

import correction.tp2.polypizz.Pizza;


public class Test{
	public static void main(String[] args) {
		
		Table<Integer> table = new Table<Integer>(20);
		
		table.add(new Integer(5));
		table.add(new Integer(20));
		table.add(new Integer(45));
		table.add(new Integer(45));
		
		Iterator<Integer> it = table.getIterator();
		
		Integer o;
		while(it.hasNext()){
			o = it.next();
			System.out.println(o);
		}
		
		
		Table<Pizza> tablePizza = new Table<Pizza>(20);
	}
}
