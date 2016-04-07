package correction.tp2.polypizz;

import java.util.ArrayList;

public class Pizza {
	private Pate pate;
	private Sauce sauce;
	private ArrayList<Ingredient> ingredient;
	
	public Pizza(Pate pate, Sauce sauce, ArrayList<Ingredient> ingredient) {
		super();
		this.pate = pate;
		this.sauce = sauce;
		this.ingredient = new ArrayList<Ingredient>();
		for(Ingredient i : ingredient){
			this.ingredient.add(i);
		}
	}
	
	public Pate getPate() {
		return pate;
	}
	public void setPate(Pate pate) {
		this.pate = pate;
	}
	public Sauce getSauce() {
		return sauce;
	}
	public void setSauce(Sauce sauce) {
		this.sauce = sauce;
	}
	public ArrayList<Ingredient> getIngredient() {
		return ingredient;
	}
	public void setIngredient(ArrayList<Ingredient> ingredient) {
		this.ingredient = ingredient;
	}
	
	
}
