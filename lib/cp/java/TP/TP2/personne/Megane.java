package correction.tp2.personne;

public class Megane extends Renault {
	
	public Megane(String couleur) {
		super(couleur);
		// TODO Auto-generated constructor stub
	}

	@Override
	public void accelerer() {
		// TODO Auto-generated method stub
		System.out.println("Megane - Accélérer");
	}

	@Override
	public void freiner() {
		// TODO Auto-generated method stub
		System.out.println("Megane - Freiner");
	}
}
