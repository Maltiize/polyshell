package correction.tp4.personneSecu;

import java.util.*;
import java.io.*;

public class Secu  implements Cloneable{
	private Set<Personne> ensemblePersonne;
	
	public Secu(){
		this.ensemblePersonne = new HashSet<>();
	}
	
	public void add(Personne p){
		this.ensemblePersonne.add(p);
	}
	
	
	public String toString(){
		String s = new String();
		
		for(Personne p : this.ensemblePersonne){
			s += "["+p.toString()+"]";
		}
		
		return s;
	}
	
	public Object clone() throws CloneNotSupportedException {
		Secu s = (Secu)super.clone();
		
		s.ensemblePersonne = new HashSet<Personne>();
		for(Personne p : this.ensemblePersonne){
			s.ensemblePersonne.add((Personne)p.clone());
		}
		return s;
	}
	

	 
	 public void serialise(File f){
		 try{
			 FileOutputStream file = new FileOutputStream(f);
			 ObjectOutputStream out = new ObjectOutputStream(file);
			 
			 out.writeObject(new Integer(this.ensemblePersonne.size()));
			 for(Personne p : this.ensemblePersonne){
				 out.writeObject(p);
			 }
			 
		 }catch(Exception e){
			 System.out.println("Erreur "+e.getMessage());
		 }
	 }
	 
	 public void deserialise(File f){
		 try{
			 FileInputStream file = new FileInputStream(f);
			 ObjectInputStream in = new ObjectInputStream(file);
			 
			 Integer t = (Integer)in.readObject();
			 for(int i = 0; i < t.intValue(); i++){
				 this.ensemblePersonne.add((Personne)in.readObject());
			 }
			 
		 }catch(Exception e){
			 System.out.println("Erreur "+e.getMessage());
		 }
	 }
	 
	 public static class Test{
			public static void main(String[] args) {
				// TODO Auto-generated method stub
				Personne p1 = new Personne("predeau", "paul", Genre.MASCULIN, 1234);
				Personne p2 = new Personne("Mac", "queen", Genre.MASCULIN, 12349);
				Personne p3 = new Personne("predeau", "paul", Genre.MASCULIN, 12345);
				
				Personne p4 = new Personne("predeau", "paul", Genre.MASCULIN, 123456);
	
				Secu s = new Secu();
				
				s.add(p1);
				s.add(p2);
				s.add(p3);
				
				File file = new File("test.obj");
				
				s.serialise(file);
				
				Secu t = new Secu();
				t.deserialise(file);
				System.out.println(t);
				
				System.out.println(Genre.valueOf("MASCULIN"));
				System.out.println(Genre.values());
			}
		}
	 
}
