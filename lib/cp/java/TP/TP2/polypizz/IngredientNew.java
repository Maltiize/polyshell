package correction.tp2.polypizz;

public class IngredientNew extends PizzaNew {

	private PizzaNew contenant;
	
	public IngredientNew(PizzaNew p){
		this.contenant = p;
	}
	
	@Override
	public String toString() {
		// TODO Auto-generated method stub
		return contenant.toString();
	}
}
