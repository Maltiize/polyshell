package correction.tp1.voiture;

public class Test {
	public static void main(String[] args) {
		
		Roue[] roues1 = new Roue[4];
		roues1[0] = new Roue(EnumMarqueRoue.Polylin, EnumModeleRoue.Super, 400);
		roues1[1] = new Roue(EnumMarqueRoue.Polylin, EnumModeleRoue.Super, 400);
		roues1[2] = new Roue(EnumMarqueRoue.Polylin, EnumModeleRoue.Super, 400);
		roues1[3] = new Roue(EnumMarqueRoue.Polylin, EnumModeleRoue.Super, 400);
		
		Moteur moteur1 = new Moteur(EnumPuissance.p80ch, 2000);
		
		Voiture polygeotStandard = new Voiture(EnumMarqueVoiture.Polygeot, EnumModeleVoiture.A, 8000, roues1, moteur1);
		
		System.out.println(polygeotStandard);
		
		Voiture polygeotStandard2 = FactoryVoiture.getVoiturePolygeot(EnumGammeVoiture.standard);
		
		System.out.println(polygeotStandard2);
	}
}
