package correction.tp5.instrument;

public class Batterie extends Instrument {

	private static int nbreBatterie = 0;
	private static final String TYPE = "Batterie";
	
	public Batterie(Categorie categorie) {
		super(categorie, TYPE, nbreBatterie++);
	}

}
