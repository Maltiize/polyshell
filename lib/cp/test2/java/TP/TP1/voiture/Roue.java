package correction.tp1.voiture;

public class Roue {
	
	private EnumMarqueRoue marque;
	private EnumModeleRoue modele;
	private int prix;
	
	public Roue(EnumMarqueRoue marque, EnumModeleRoue modele, int prix) {
		super();
		this.marque = marque;
		this.modele = modele;
		this.prix = prix;
	}

	public EnumMarqueRoue getMarque() {
		return marque;
	}

	public void setMarque(EnumMarqueRoue marque) {
		this.marque = marque;
	}

	public EnumModeleRoue getModele() {
		return modele;
	}

	public void setModele(EnumModeleRoue modele) {
		this.modele = modele;
	}

	public int getPrix() {
		return prix;
	}

	public void setPrix(int prix) {
		this.prix = prix;
	}

	@Override
	public String toString() {
		return "Roue [marque=" + marque + ", modele=" + modele + ", prix="
				+ prix + "]";
	}
	

}
