package correction.tp2.utiliteClasseAbstraite;

import java.util.AbstractList;
import java.util.ArrayList;

public class Test {
	public static void main(String[] args) {
		
		AbstractList<Integer> listInteger = new ArrayList<Integer>();
		
		for(int i =0; i < 10; i++){
			listInteger.add(i);
		}
		
		for(int i =0; i < 10; i++){
			System.out.println("i="+listInteger.get(i));
		}
	}
}
