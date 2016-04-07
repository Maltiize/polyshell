package correction.examTp1415.graphe;

import java.util.Stack;

public class ParcoursProfondeur extends ParcoursGraphe {

	private Stack<Noeud> stacks;
	
	public ParcoursProfondeur(Graphe graphe){
		super(graphe);
		this.stacks = new Stack<>();
		
		this.stacks.push(graphe.getInitState());
	}

	@Override
	public boolean hasNext() {
		return !this.stacks.isEmpty();
	}

	@Override
	public Noeud next() {
		
		Noeud noeud = this.stacks.pop();
		this.setAsMarked(noeud);
		
		for(Noeud next : noeud.getSuivants()){
			if(!this.isMarked(next)){
				this.stacks.push(next);
			}
		}
		
		return noeud;
	}


}
