package correction.tp4.personneSecu;

import java.io.IOException;
import java.util.*;
import java.io.*;


public class Personne implements Cloneable, Serializable {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private String nom, prenom;
	private Set<Personne> listeEnfants;
	private Genre genre;
	private int secu;

	public Personne(String nom, String prenom, Genre genre, int secu){
		this.nom = nom;
		this.prenom = prenom;
		this.genre = genre;
		this.secu = secu;
		this.listeEnfants = new HashSet<Personne>();
	}
		
	public boolean equals(Object p){
		
		if(!(p instanceof Personne)){
			return false;
		}
		
		Personne pers = (Personne)p;
		if (this.secu != pers.secu){	
			return false;
		}else{
			return true;
		}
	}
	
	public int hashCode(){
		return this.secu;
	}
	
	public Object clone() throws CloneNotSupportedException {
		Personne p = (Personne)super.clone();
		
		p.listeEnfants = new HashSet<Personne>();
		
		for(Personne cpt : this.listeEnfants){
			p.listeEnfants.add(cpt);
		}
		return p;
	}
	
	public String toString(){
		return this.nom + ","+ this.prenom + "," + this.genre+","+this.secu;
	}
	
	private void writeObject(java.io.ObjectOutputStream out) throws IOException{
		out.defaultWriteObject(); 
	}
	 
	private void readObject(java.io.ObjectInputStream in) throws IOException, ClassNotFoundException{
		 in.defaultReadObject();
	}
	
	public static class Test{
		public static void main(String[] args) {
			// TODO Auto-generated method stub
			Personne p1 = new Personne("predeau", "paul", Genre.MASCULIN, 1234);
			Personne p2 = new Personne("predeau", "paul", Genre.MASCULIN, 1234);
			Personne p3 = new Personne("predeau", "paul", Genre.MASCULIN, 12345);
			
			Personne p4 = new Personne("predeau", "paul", Genre.MASCULIN, 123456);
			p2.getListeEnfants().add(p4);
			
			p1.getListeEnfants().add(p2);
			p1.getListeEnfants().add(p3);
			
			try{
				Personne p5 = (Personne)p1.clone();
			}catch(Exception e){
				System.out.println("Erreur"+e.getMessage());
			}
			
			
			Secu s = new Secu();
			
			s.add(p1);
			s.add(p2);
			s.add(p3);
			
			System.out.println(s);
			
		}
	}



	public String getNom() {
		return nom;
	}



	public void setNom(String nom) {
		this.nom = nom;
	}



	public String getPrenom() {
		return prenom;
	}



	public void setPrenom(String prenom) {
		this.prenom = prenom;
	}



	public Set<Personne> getListeEnfants() {
		return listeEnfants;
	}



	public void setListeEnfants(Set<Personne> listeEnfants) {
		this.listeEnfants = listeEnfants;
	}



	public Genre getGenre() {
		return genre;
	}



	public void setGenre(Genre genre) {
		this.genre = genre;
	}



	public int getSecu() {
		return secu;
	}



	public void setSecu(int secu) {
		this.secu = secu;
	}

}
