package correction.tp1.voiture;

public class FactoryVoiture {
	public static Voiture getVoiturePolygeot(EnumGammeVoiture gamme){
		
		Roue[] roues;
		Moteur moteur;
		
		switch (gamme) {
		case standard:
			roues = new Roue[4];
			roues[0] = new Roue(EnumMarqueRoue.Polylin, EnumModeleRoue.Super, 400);
			roues[1] = new Roue(EnumMarqueRoue.Polylin, EnumModeleRoue.Super, 400);
			roues[2] = new Roue(EnumMarqueRoue.Polylin, EnumModeleRoue.Super, 400);
			roues[3] = new Roue(EnumMarqueRoue.Polylin, EnumModeleRoue.Super, 400);
			
			moteur = new Moteur(EnumPuissance.p80ch, 2000);
			
			return new Voiture(EnumMarqueVoiture.Polygeot, EnumModeleVoiture.A, 8000, roues, moteur);
		
		case classic:
			// a faire
			return null;
		case privilege:
		default:
			// a faire
			return null;
		}
	}
}
