package correction.tp5.operande;

public abstract class Operateur extends Expression {
	
	private Expression left;
	private Expression right;
	private String operateur;
	
	public Operateur(Expression left, Expression right, String operateur){
		this.left = left;
		this.right = right;
		this.operateur = operateur;
	}
	
	@Override
	public String toString() {
		return "("+ this.left.toString() + " " + this.operateur + " " + this.right + ")";
	}

}
