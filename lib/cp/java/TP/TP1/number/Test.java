package correction.tp1.number;

public class Test {
	public static void main(String[] args) {
		GestionMesure gestionMesure = new GestionMesure();
		
		gestionMesure.add(1000000000);
		gestionMesure.add(1);
		gestionMesure.add(2);
		gestionMesure.add(3);
		gestionMesure.add(4);
		gestionMesure.add(5);
		gestionMesure.add(6);
		
		System.out.println("Ecart type: "+gestionMesure.getEcartType());
		System.out.println("Moyenne: "+gestionMesure.getMoyenne());
		System.out.println("Médianne: "+gestionMesure.getMedianne());
		System.out.println("Variance: "+gestionMesure.getVariance());
		
		
	}
}
