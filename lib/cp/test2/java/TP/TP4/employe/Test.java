package correction.tp4.employe;

public class Test {
	public static void main(String[] args) {
		Manager manager1 = new Manager("aN", "aP", 28);
		
		Employe employe1 = new Developpeur("ep1", "eN1", 22, manager1);
		Employe employe2 = new Developpeur("ep2", "eN2", 23, manager1);
		
		manager1.addEmploye(employe1);
		manager1.addEmploye(employe2);
		
		Manager manager2 = new Manager("aN2", "aP2", 35);
		
		Employe employe3 = new Developpeur("ep3", "eN3", 24, manager2);
		Employe employe4 = new Developpeur("ep4", "eN4", 25, manager2);
		
		manager2.addEmploye(employe3);
		manager2.addEmploye(employe4);
		manager2.addEmploye(manager1);
		
		System.out.println(manager2);
		
	}
}
