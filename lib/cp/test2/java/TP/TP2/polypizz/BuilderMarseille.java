package correction.tp2.polypizz;


public class BuilderMarseille extends Builder {

	
	
	public BuilderMarseille() {
		super(new FactoryPizzaMarseille());
		// TODO Auto-generated constructor stub
	}

	@Override
	public void ajoutIngredient() {
		// TODO Auto-generated method stub
		System.out.println("Builder Marseille - AjoutIngredient"+p);
	}

	@Override
	public void ajoutSauce() {
		// TODO Auto-generated method stub
		System.out.println("Builder Marseille - AjoutSauce"+p);
	}

	@Override
	public void cuisson() {
		// TODO Auto-generated method stub
		System.out.println("Builder Marseille - Cuisson"+p);
	}

	@Override
	public void preparationPate() {
		// TODO Auto-generated method stub
		System.out.println("Builder Marseille - PreparationPate"+p);
	}


}
