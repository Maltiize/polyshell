package correction.examTp1314.cocktail;

public class Test {
	public static void main(String[] args) {
		
		Cocktail indien = FactoryCocktail.getIndien();
		System.out.println(indien);
		
		Cocktail abricotFrappe = FactoryCocktail.getAbricotFrappe();
		System.out.println(abricotFrappe);
		
		Cocktail jusAbricot = new JusAbricot(null, 10);
		Cocktail copy = null;
		
		try {
			copy = (Cocktail)abricotFrappe.clone();
			
			System.out.println(copy);
			System.out.println(String.valueOf(copy == abricotFrappe));
			
		} catch (CloneNotSupportedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
}
