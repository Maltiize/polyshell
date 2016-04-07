package correction.tp2.polypizz;

import correction.tp2.polypizz.Builder.TypePizza;

public class BuilderNantes extends Builder{

	public BuilderNantes() {
		super(new FactoryPizzaNantes());
	}

	
	@Override
	public void ajoutIngredient() {
		// TODO Auto-generated method stub
		System.out.println("Builder Nantes - AjoutIngredient"+p);
	}

	@Override
	public void ajoutSauce() {
		// TODO Auto-generated method stub
		System.out.println("Builder Nantes - AjoutSauce"+p);
	}

	@Override
	public void cuisson() {
		// TODO Auto-generated method stub
		System.out.println("Builder Nantes - Cuisson"+p);
	}

	@Override
	public void preparationPate() {
		// TODO Auto-generated method stub
		System.out.println("Builder Nantes - PreparationPate"+p);
	}

}
