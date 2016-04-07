package correction.examTp1415.graphe;

import java.util.Iterator;

public class Test {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		Noeud start = new Noeud(1, TypeNoeud.INIT);
		Noeud eight = new Noeud(8);
		Noeud ten = new Noeud(10, TypeNoeud.FINAL);
		Noeud seven = new Noeud(7, TypeNoeud.FINAL);
		start.ajouterSuivant(eight);
		start.ajouterSuivant(ten);
		start.ajouterSuivant(seven);
		
		Noeud four = new Noeud(4, TypeNoeud.FINAL);
		Noeud five = new Noeud(5, TypeNoeud.FINAL);
		eight.ajouterSuivant(four);
		eight.ajouterSuivant(five);
		
		five.ajouterSuivant(start);
		
		Graphe graphe = new Graphe(start, TypeParcours.Largeur);
		
		Iterator<Noeud> it = graphe.iterator();
		Noeud current = null;
		while(it.hasNext()){
			current = it.next();
			System.out.println(current);
		}
		
		System.out.println("\n");
		
		Graphe graphe2 = new Graphe(start, TypeParcours.Profondeur);
		
		Iterator<Noeud> it2 = graphe2.iterator();
		Noeud current2 = null;
		while(it2.hasNext()){
			current2 = it2.next();
			System.out.println(current2);
		}
		
		System.out.println("\n");
		
		for(Noeud n : graphe){
			System.out.println(n);
		}
		
		System.out.println("\n");
		
		for(Noeud n : graphe2){
			System.out.println(n);
		}
	
		try{
		
			graphe.verifGraphe();
			
		}catch(ExceptionBadGraph e){
			System.out.println(e.getMessage());
		}
		
		System.out.println("\n Sum graphe:"+graphe.getSum());
	}

}
