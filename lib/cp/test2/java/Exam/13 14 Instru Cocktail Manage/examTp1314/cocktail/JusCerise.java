package correction.examTp1314.cocktail;

public class JusCerise extends DecorateurCocktail {
	
	public JusCerise(Cocktail ingredient, int dose) {
		super(ingredient, dose);
		
	}

	@Override
	public String toString() {
		return "JusCerise [" + super.toString() + "]";
	}
}
