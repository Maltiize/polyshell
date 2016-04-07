package correction.tp5.operande;

public class Operande extends Expression {
	private int valeur;
	
	public Operande(int valeur) {
		this.valeur = valeur;
	}
	
	@Override
	public String toString() {
		return Integer.toString(this.valeur);
	}
	
}
