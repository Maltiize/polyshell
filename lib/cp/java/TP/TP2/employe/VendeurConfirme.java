package employe;

import java.util.Iterator;

import produit.Produit;

public class VendeurConfirme extends Employe{
	public VendeurConfirme(String nom, String prenom, int age) {
		super(nom, prenom, age);
		System.out.println("Création d'une instance de la classe VendeurConfirme");
	}

	@Override
	public boolean isRightToSellProduct() {
		return true;
	}

	@Override
	public double getPrime() {
		double retour = 0;
		for(Iterator<Produit> iter = this.getListeProduits().iterator();iter.hasNext();){
			retour += iter.next().getPrix()*0.25;
		}
		return retour;
	}
}
