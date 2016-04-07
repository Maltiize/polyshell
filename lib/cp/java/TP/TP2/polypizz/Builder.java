package correction.tp2.polypizz;

public abstract class Builder {

	protected Pizza p;
	protected FactoryPizza f;
	
	public Builder(FactoryPizza f){
		this.f = f;
	}
	
	public enum TypePizza {
		Margherita, Vegetarienne 
	}
	
	public Pizza preparerPizza(TypePizza type){
		
		switch (type) {
		case Margherita:
			p = f.getMargherita();
			break;
		case Vegetarienne:
			p = f.getVegetarienne();
			break;
		default:
			break;
		}
		
		this.preparationPate();
		this.ajoutSauce();
		this.ajoutIngredient();
		this.cuisson();
		
		return p;
	}
	
	public abstract void preparationPate();
	public abstract void ajoutSauce();
	public abstract void ajoutIngredient();
	public abstract void cuisson();
	
}
