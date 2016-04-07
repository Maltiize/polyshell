package correction.tp3.etudiant;

import java.util.Collections;
import java.util.Vector;

public class Test {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Etudiant etu1 = new Etudiant("Pigeau", "Antoine", 12.5);
		Etudiant etu2 = new Etudiant("Pigeau", "Arthur", 9.3);
		Etudiant etu3 = new Etudiant("Pigeau", "Ethan", 14.55);
		
		Vector<Etudiant> etudiants = new Vector<>();
		
		etudiants.add(etu1);
		etudiants.add(etu2);
		etudiants.add(etu3);
		
		Collections.sort(etudiants);
		
		System.out.println(etudiants);
		
		Foo.method();
		Bar.method();
	}
	
	public static void test(){
		
	}
	
	static class Foo {
	    public static void method() {
	        System.out.println("in Foo");
	    }
	} 

	static class Bar extends Foo {
	    public static void method() {
	        System.out.println("in Bar");
	    }
	}

}
