package correction.tp1.personne;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class GestionPersonne {

	private Set<Personne> personnes;


	public GestionPersonne(){
		this.personnes = new HashSet<>();
	}

	public boolean addPersonne(Personne p){
		return this.personnes.add(p);
	}

	public float getAgeMoyen(){

		float sum = 0.0f;

		for(Personne p: this.personnes){
			sum += p.getAge();
		}

		return sum / this.personnes.size();
	}

	public Personne getPersonne(String nom){

		Personne find = null;

		for(Personne p : personnes){
			if(p.getNom().equals(nom)){
				find = p;
				break;
			}
		}

		return find;
	}

	public Personne getPersonne(String nom, String prenom){
		Personne find = null;

		for(Personne p : personnes){
			if(p.getNom().equals(nom) && p.getPrenom().equals(prenom)){
				find = p;
				break;
			}
		}

		return find;
	}


	@Override
	public String toString() {

		List<Personne> list = new ArrayList<Personne>(personnes);
		Collections.sort(list);

		return list.toString();
	}
}
