package correction.tp1.voiture;

public class Moteur {
	
	private EnumPuissance puissance;
	private int prix;
	
	public EnumPuissance getPuissance() {
		return puissance;
	}

	public void setPuissance(EnumPuissance puissance) {
		this.puissance = puissance;
	}

	public int getPrix() {
		return prix;
	}

	public void setPrix(int prix) {
		this.prix = prix;
	}

	public Moteur(EnumPuissance puissance, int prix) {
		super();
		this.puissance = puissance;
		this.prix = prix;
	}

	@Override
	public String toString() {
		return "Moteur [puissance=" + puissance + ", prix=" + prix + "]";
	}
	
	

}
