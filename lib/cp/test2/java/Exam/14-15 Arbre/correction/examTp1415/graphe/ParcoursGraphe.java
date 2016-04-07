package correction.examTp1415.graphe;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.function.Consumer;

public abstract class ParcoursGraphe implements Iterator<Noeud> {

	protected Graphe graphe;
	protected List<Noeud> markedNoeuds;
	
	public ParcoursGraphe(Graphe graphe){
		this.graphe = graphe;
		this.markedNoeuds = new ArrayList<Noeud>();
	}
	
	@Override
	public void forEachRemaining(Consumer<? super Noeud> arg0){
		throw new UnsupportedOperationException();
	}

	@Override
	public abstract boolean hasNext();

	@Override
	public abstract Noeud next();

	@Override
	public void remove(){
		throw new UnsupportedOperationException();
	}

	protected boolean isMarked(Noeud noeud){
		return this.markedNoeuds.contains(noeud);
	}
	
	protected void setAsMarked(Noeud noeud){
		this.markedNoeuds.add(noeud);
	}

}
