package employe;

import java.util.Iterator;

import produit.Produit;

public class VendeurDebutant extends Employe{

	public VendeurDebutant(String nom, String prenom, int age) {
		super(nom, prenom, age);
		System.out.println("Création d'une instance de la classe VendeurDebutant");
	}

	public boolean isRightToSellProduct(){
		boolean retour = true;
		for(Iterator<Produit> iter = this.getListeProduits().iterator();iter.hasNext();){
			if(iter.next().getPrix()>1000){
				retour = false;
			}
		}
		return retour;
	}

	@Override
	public double getPrime() {
		double retour = 0;
		for(Iterator<Produit> iter = this.getListeProduits().iterator();iter.hasNext();){
			retour += iter.next().getPrix()*0.15;
		}
		return retour;
	}
}
