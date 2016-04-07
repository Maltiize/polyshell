package correction.tp2.personne;

import java.util.ArrayList;

public abstract class Voiture {
	private int reference;
	private static int referenceCount = 0;
	
	private String couleur;
	private ArrayList<Option> optionliste;
	
	
	
	public Voiture(String couleur) {
		super();
		this.reference = referenceCount++;
		this.couleur = couleur;
		this.optionliste = new ArrayList<Option>();
	}
	public abstract void freiner();
	public abstract void accelerer();
	
	public final int getReference() {
		return reference;
	}
	public final void setReference(int reference) {
		this.reference = reference;
	}
	public String getCouleur() {
		return couleur;
	}
	public void setCouleur(String couleur) {
		this.couleur = couleur;
	}
	public ArrayList<Option> getOptionliste() {
		return optionliste;
	}
	public void setOptionliste(ArrayList<Option> optionliste) {
		this.optionliste = optionliste;
	}
	
	
	@Override
	public String toString() {
		return "Voiture [couleur=" + couleur + ", optionliste=" + optionliste
				+ ", reference=" + reference + "]";
	}
	
	
	
	
}
