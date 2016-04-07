package correction.examTp1314.cocktail;

public abstract class DecorateurCocktail extends Cocktail {
	
	private Cocktail ingredient;
	
	private int dose;

	public DecorateurCocktail(Cocktail ingredient, int dose) {
		super();
		this.ingredient = ingredient;
		this.dose = dose;
	}

	@Override
	public String toString() {
		return "ingredient=" + ingredient + ", dose="
				+ dose;
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		
		DecorateurCocktail clone = (DecorateurCocktail)super.clone();
		
		if(this.ingredient != null){
			clone.ingredient = (Cocktail)(this.ingredient.clone());
		}
		
		return super.clone();
	}
	
}
