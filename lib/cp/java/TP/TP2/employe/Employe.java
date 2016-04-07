package employe;

import java.util.ArrayList;
import java.util.Iterator;

import produit.Produit;
import produit.ProduitEcolo;

public abstract class Employe {
	protected String nom;
	protected String prenom;
	protected int age;
	protected ArrayList<Produit> listeProduits;

	public Employe(String nom, String prenom, int age) {
		this.nom = nom;
		this.prenom = prenom;
		this.age = age;
		ArrayList<Produit> listeProduits = new ArrayList<Produit>();
		System.out.println("Création d'une instance de la classe Employe");
	}

	@Override
	public String toString() {
		return "Employe [nom=" + nom + ", prenom=" + prenom + ", age=" + age
				+ "]";
	}

	public ArrayList<Produit> getListeProduits() {
		return listeProduits;
	}

	public void setListeProduits(ArrayList<Produit> listeProduits) {
		this.listeProduits = listeProduits;
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

	public int getAge() {
		return age;
	}

	public void setAge(int age) {
		this.age = age;
	}

	public abstract boolean isRightToSellProduct();

	public abstract double getPrime();

	public double getPercentOfEco(){
		double nb_produits_eco = 0;
		double nb_produits = 0;
		for(Iterator<Produit> iter = this.getListeProduits().iterator();iter.hasNext();){
			if(iter.next() instanceof ProduitEcolo){
				nb_produits_eco += 1;
			}
			nb_produits += 1;
		}
		return nb_produits_eco/nb_produits*100;
	}

}