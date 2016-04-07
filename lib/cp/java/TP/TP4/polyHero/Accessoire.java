package correction.tp4.polyHero;

public abstract class Accessoire extends Hero{
	
	private Hero myHero;
	
	public Accessoire(Hero hero){
		this.myHero = hero;
	}
	
	public String getDescription(){
		return this.myHero.getDescription();
	}
	
}
