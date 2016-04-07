package correction.tp2.figure;

public class Test {
	public static void main(String[] args) {
		
		Figure cercle = new Cercle();
		Figure ligne = new Ligne();
		
		FigureComposite figureComposite = new FigureComposite(cercle, ligne);
		
		System.out.println(figureComposite);
		
	}
}
