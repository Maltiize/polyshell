package correction.tp2.personne;

import java.util.ArrayList;

public final class Personne {
	private String nom;
	private String prenom;
	private String adresse;
	private String numeroTelephone;
	
	private ArrayList<Voiture> listVoiture;
	
	public Personne(String nom, String prenom, String adresse,
			String numeroTelephone) {
		super();
		this.nom = nom;
		this.prenom = prenom;
		this.adresse = adresse;
		this.numeroTelephone = numeroTelephone;
		this.listVoiture = new ArrayList<Voiture>();
	}

	public Personne(String nom, String prenom) {
		this(nom, prenom, null, null);
	}

	public ArrayList<Voiture> getListVoiture() {
		return listVoiture;
	}

	public void traitementGenerique(){
		for(Voiture v : this.listVoiture){
			v.accelerer();
			v.freiner();
			v.toString();
		}
	}
	
	

}
