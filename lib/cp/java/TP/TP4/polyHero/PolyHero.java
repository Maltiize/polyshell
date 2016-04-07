package correction.tp4.polyHero;

public class PolyHero extends Hero {
	private String name;
	
	public PolyHero(String name){
		this.name = name;
	}

	@Override
	public String getDescription() {
		// TODO Auto-generated method stub
		return this.name;
	}
}
