package correction.examTp1415.graphe;

import java.util.HashSet;
import java.util.Set;

public class Noeud {

	private Set<Noeud> suivants;
	private int value;
	private TypeNoeud typeNoeud;

	public Noeud(int value, TypeNoeud typeState){
		this.value = value;
		this.suivants = new HashSet<>();
		this.typeNoeud = typeState;
	}
	
	public Noeud(int value){
		this(value, TypeNoeud.INTER);
	}
	
	public boolean isStateInit() {
		return this.typeNoeud == TypeNoeud.INIT;
	}

	public boolean isStateFinal() {
		return this.typeNoeud == TypeNoeud.FINAL;
	}
	
	public int getValue() {
		return value;
	}

	public boolean ajouterSuivant(Noeud noeud){
		return this.suivants.add(noeud);
	}
	
	public boolean removeSuivant(Noeud noeud){
		return this.suivants.remove(noeud);
	}
	
	public Set<Noeud> getSuivants(){
		return this.suivants;
	}
	
	@Override
	public String toString() {
		return "Noeud [value=" + value + ", typeNoeud=" + typeNoeud+ "]";
	}
	
}
