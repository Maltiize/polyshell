package correction.tp5.instrument;

public class Guitare extends Instrument {

	private static int nbreGuitare = 0;
	private static final String TYPE = "Guitare";
	
	public Guitare(Categorie categorie) {
		super(categorie, TYPE, nbreGuitare++);
	}

}
