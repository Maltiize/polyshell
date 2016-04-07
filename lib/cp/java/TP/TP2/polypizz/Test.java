package correction.tp2.polypizz;

import java.util.ArrayList;

import correction.tp2.polypizz.Builder.TypePizza;

public class Test {
	public static void main(String[] args) {
		Ingredient ing1 = new Mozzarella();
		Ingredient ing2 = new Mozzarella();
		ArrayList<Ingredient> listIngredient = new ArrayList<Ingredient>();
		listIngredient.add(ing1);
		listIngredient.add(ing2);
		
		Pate pateFine = new PateFine();
		Sauce sauceTomate = new SauceTomate();
		
		Pizza pizzaMargherita = new Pizza(pateFine, sauceTomate, listIngredient);
		
		listIngredient.clear();
		listIngredient.add(new Champignon());
		listIngredient.add(new Mozzarella());
		Pate pateFine2 = new PateFine();
		Sauce sauceTomate2 = new SauceTomate();
		
		Pizza pizzaVegetarienne = new Pizza(pateFine2, sauceTomate2, listIngredient);
		
		// Factory
		
		FactoryPizza factoryNantes = new FactoryPizzaNantes();
		Pizza margheritaNantes = factoryNantes.getMargherita();
		
		// Builder
		
		Pizza pizzaMargheritaNantes = new BuilderNantes().preparerPizza(TypePizza.Margherita);
		Pizza pizzaMargheritaMarseille = new BuilderMarseille().preparerPizza(TypePizza.Vegetarienne);
		
		// Decorator
		PizzaNew margheritaNew = new SauceNew(new MozzarellaNew(new PateNew()));
		
		System.out.println(margheritaNew.toString());
		
	}
}
