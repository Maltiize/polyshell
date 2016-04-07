package correction.tp4.polyHero;

public abstract class Hero {
	
	public abstract String getDescription(); 
	
	public static void main(String[] args) {
		Hero poly = new PolyHero("Bob");
		Accessoire casque = new Casque(poly);
		Accessoire ceinture = new Ceinture(casque);

		System.out.println(ceinture.getDescription()); // affichage de "Bob : casque, ceinture"
	}
}
