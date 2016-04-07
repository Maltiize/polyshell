package correction.examTp1415.graphe;

import java.util.ArrayDeque;
import java.util.Queue;

public class ParcoursLargeur extends ParcoursGraphe {

	private Queue<Noeud> queues;
	
	public ParcoursLargeur(Graphe graphe){
		super(graphe);
		this.queues = new ArrayDeque<>();
		
		this.queues.add(graphe.getInitState());
	}

	@Override
	public boolean hasNext() {
		return !this.queues.isEmpty();
	}

	@Override
	public Noeud next() {
		
		Noeud noeud = this.queues.poll();
		this.setAsMarked(noeud);
		
		for(Noeud next : noeud.getSuivants()){
			if(!this.isMarked(next)){
				this.queues.add(next);
			}
		}
		
		return noeud;
	}

}
