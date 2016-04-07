package correction.tp1.personne;


public class Test {
	public static void main(String[] args) {
		
		Personne p1 = new Personne();
		Personne p2 = new Personne("Pigeau", "Paul", 45, null, null);
		Personne p3 = new Personne("Pigeau", "Linda", 45, null, null);
		Personne p4 = new Personne("Pigeau", "Antoine", 36, p2, p3);
		
		System.out.println(p4);
		
		GestionPersonne gestionPersonne = new GestionPersonne();
		
		gestionPersonne.addPersonne(p1);
		gestionPersonne.addPersonne(p2);
		gestionPersonne.addPersonne(p3);
		gestionPersonne.addPersonne(p4);
		
		System.out.println(gestionPersonne);
		
		System.out.println("\nTrouver Personne\n");
		System.out.println(gestionPersonne.getPersonne("Pigeau"));
		System.out.println(gestionPersonne.getPersonne("Pigeau", "Paul"));
	}
}
