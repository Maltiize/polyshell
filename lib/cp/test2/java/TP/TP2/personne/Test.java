package correction.tp2.personne;

public class Test {
	
	public static void main(String[] args) {
		
		Peugeot207 p = new Peugeot207("Rouge");
		Option option1 = new Option("AirBag");
		Option option2 = new Option("ABS");
		p.getOptionliste().add(option1);
		p.getOptionliste().add(option2);
		
		Personne personne = new Personne("Ted","Mosby");
		personne.getListVoiture().add(p);
		
		personne.traitementGenerique();
		
		System.out.println(p);
	}
	
}
