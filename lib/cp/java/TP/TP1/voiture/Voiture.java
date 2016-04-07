package correction.tp1.voiture;

import java.util.Arrays;

public class Voiture {
	
	private EnumMarqueVoiture marque;
	private EnumModeleVoiture modele;
	private int prix;
	
	private Roue[] roues;
	private Moteur moteur;
	
	public Voiture(EnumMarqueVoiture marque, EnumModeleVoiture modele,
			int prix, Roue[] roues, Moteur moteur) {
		super();
		this.marque = marque;
		this.modele = modele;
		this.prix = prix;
		this.roues = roues;
		this.moteur = moteur;
	}

	public EnumMarqueVoiture getMarque() {
		return marque;
	}

	public void setMarque(EnumMarqueVoiture marque) {
		this.marque = marque;
	}

	public EnumModeleVoiture getModele() {
		return modele;
	}

	public void setModele(EnumModeleVoiture modele) {
		this.modele = modele;
	}

	public int getPrix() {
		return this.prix + this.roues[0].getPrix()*4 + this.moteur.getPrix();
	}

	public void setPrix(int prix) {
		this.prix = prix;
	}

	public Roue[] getRoues() {
		return roues;
	}

	public void setRoues(Roue[] roues) {
		this.roues = roues;
	}

	public Moteur getMoteur() {
		return moteur;
	}

	public void setMoteur(Moteur moteur) {
		this.moteur = moteur;
	}

	@Override
	public String toString() {
		return "Voiture [marque=" + marque + ", modele=" + modele + ", prix="
				+ prix + ", roues=" + Arrays.toString(roues) + ", moteur="
				+ moteur + "]";
	}
	
}
