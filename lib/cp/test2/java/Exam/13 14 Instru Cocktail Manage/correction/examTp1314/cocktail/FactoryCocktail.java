package correction.examTp1314.cocktail;

public class FactoryCocktail {

	public static Cocktail getIndien(){
		return new SodaOrange(new SiropGrenadine(new Contenant(), 1), 10);
	}
	
	public static Cocktail getAbricotFrappe(){
		return new JusAbricot(new JusAnanas(new JusCitronVert(new JusCerise(new Contenant(),1), 1), 3), 4);
	}
	
	
}
