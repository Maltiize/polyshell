package correction.examTp1314.cocktail;

public class JusAbricot extends DecorateurCocktail {
	
	public JusAbricot(Cocktail ingredient, int dose) {
		super(ingredient, dose);
		
	}

	@Override
	public String toString() {
		return "JusAbricot [" + super.toString() + "]";
	}
}
