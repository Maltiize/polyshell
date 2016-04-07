package correction.tp5.instrument;

public enum Categorie {
	HautGamme(1000), MoyenGamme(500), BasGamme(100);
	
	private int prix;
	
	private Categorie(int prix){
		this.prix = prix;
	}
	
	public int getPrix(){
		return this.prix;
	}
}
