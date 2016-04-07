package correction.examTp1314.cocktail;

public class JusAnanas extends DecorateurCocktail {
	
	public JusAnanas(Cocktail ingredient, int dose) {
		super(ingredient, dose);
		
	}

	@Override
	public String toString() {
		return "JusAnanas [" + super.toString() + "]";
	}
}
