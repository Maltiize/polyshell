package correction.tp2.polypizz;

import java.util.ArrayList;

public class FactoryPizzaNantes extends FactoryPizza {
	
	@Override
	public Pizza getMargherita(){
		Pizza pizza = null;
		
		Ingredient ing1 = new Mozzarella();
		Ingredient ing2 = new Mozzarella();
		ArrayList<Ingredient> listIngredient = new ArrayList<Ingredient>();
		listIngredient.add(ing1);
		listIngredient.add(ing2);
		
		Pate pateFine = new PateFine();
		Sauce sauceTomate = new SauceTomate();
		
		pizza = new Pizza(pateFine, sauceTomate, listIngredient);
		
		return pizza;
	}


	@Override
	public Pizza getPepperoni() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public Pizza getVegetarienne() {
		// TODO Auto-generated method stub
		return null;
	}

}
