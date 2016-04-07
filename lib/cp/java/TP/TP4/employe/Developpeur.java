package correction.tp4.employe;

public class Developpeur extends Employe {

	public Developpeur(String nom, String prenom, int age, Manager manager) {
		super(nom, prenom, age, manager);
	}

	public Developpeur(String nom, String prenom, int age) {
		super(nom, prenom, age);
	}

	@Override
	public String toString() {
		return "Developpeur ["+super.toString()+"]";
	}
	
}
