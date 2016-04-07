package correction.tp5.instrument;

public class Test {

	public static void main(String[] args) {
		Instrument batterie = new Batterie(Categorie.HautGamme);
		Instrument clavier = new Clavier(Categorie.MoyenGamme);
		Instrument batterieClone = null;
		
		try {
			batterieClone = (Batterie)batterie.clone();
		} catch (CloneNotSupportedException e) {
			e.printStackTrace();
		}
		
		GestionInstrument gestionInstrument = new GestionInstrument();
		
		try {
			gestionInstrument.addInstrument(batterie);
			gestionInstrument.addInstrument(clavier);
			gestionInstrument.addInstrument(batterieClone);
		} catch (ExceptionAlreadyAdded e) {
			// TODO Auto-generated catch block
			System.out.println(e.getMessage());
		}
		
		gestionInstrument.afficheInstrument();
		
		gestionInstrument.save();
		
		gestionInstrument.clear();
		
		gestionInstrument.load();
		
		gestionInstrument.afficheInstrument();
		
	}

}
