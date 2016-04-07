package correction.tp2.polypizz;

import java.util.ArrayList;

public class FactoryPizzaMarseille extends FactoryPizza {

	@Override
	public Pizza getMargherita() {
		// TODO Auto-generated method stub
		Pizza pizza = null;
		
		Ingredient ing1 = new Mozzarella();
		
		ArrayList<Ingredient> listIngredient = new ArrayList<Ingredient>();
		listIngredient.add(ing1);
		
		
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
Pizza pizza = null;
		
		Ingredient ing1 = new Mozzarella();
		
		ArrayList<Ingredient> listIngredient = new ArrayList<Ingredient>();
		listIngredient.add(ing1);
		
		
		Pate pateFine = new PateFine();
		Sauce sauceTomate = new SauceTomate();
		
		pizza = new Pizza(pateFine, sauceTomate, listIngredient);
		
		return pizza;
	}

}
