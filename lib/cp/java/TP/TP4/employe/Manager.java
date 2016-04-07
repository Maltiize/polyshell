package correction.tp4.employe;

import java.util.HashSet;
import java.util.Set;

public class Manager extends Employe {

	private Set<Employe> setEmploye;

	public Manager(String nom, String prenom, int age, Manager manager) {
		super(nom, prenom, age, manager);
		
		this.setEmploye = new HashSet<>();
	}
	
	public Manager(String nom, String prenom, int age) {
		this(nom, prenom, age, null);
	}

	public Set<Employe> getSetEmploye() {
		return setEmploye;
	}

	public void setSetEmploye(Set<Employe> setEmploye) {
		this.setEmploye = setEmploye;
	}	
	
	public boolean addEmploye(Employe e){
		return this.setEmploye.add(e);
	}

	@Override
	public String toString() {
		return "Manager [setEmploye=" + setEmploye + "]";
	}
	
	
}
