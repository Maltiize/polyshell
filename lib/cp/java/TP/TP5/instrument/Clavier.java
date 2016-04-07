package correction.tp5.instrument;

public class Clavier extends Instrument {

	private static int nbreClavier = 0;
	private static final String TYPE = "Clavier";
	
	public Clavier(Categorie categorie) {
		super(categorie, TYPE, nbreClavier++);
	}

}
