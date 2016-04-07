package correction.examTp1415.graphe;

import java.util.Iterator;
import java.util.Spliterator;
import java.util.function.Consumer;

public class Graphe implements Iterable<Noeud>{

	private Noeud stateInit;
	private TypeParcours typeParcours;
	
	public Graphe(Noeud stateInit, TypeParcours typeParcours){
		this.stateInit= stateInit;
		this.typeParcours = typeParcours;
	}
	
	public Noeud getInitState(){
		return this.stateInit;
	}

	@Override
	public void forEach(Consumer<? super Noeud> arg0) {
		throw new UnsupportedOperationException();
	}

	@Override
	public Iterator<Noeud> iterator() {
		
		switch (this.typeParcours) {
		case Profondeur:
			return new ParcoursProfondeur(this);
		case Largeur:
		default:
			return new ParcoursLargeur(this);
		}
	}

	@Override
	public Spliterator<Noeud> spliterator() {
		throw new UnsupportedOperationException();
	}

	public void verifGraphe() throws ExceptionBadGraph {
		
		if(!this.stateInit.isStateInit()){
			throw new ExceptionBadGraph();
		}
		
		for(Noeud noeud: this){
			
			if(noeud.getSuivants().isEmpty() && !noeud.isStateFinal()){
				throw new ExceptionBadGraph();
			}
			
		}
	
	}
	
	public int getSum(){
		int somme = 0;
		
		for(Noeud noeud: this){
			somme += noeud.getValue();
		}
		
		return somme;
	}
	
}
