package correction.tp1.arbre;

public class Test {
	public static void main(String[] args) {
		
		Element a = new Element(4);
		Element b = new Element(10);
		Element c = new Element(a, b, 8);
		
		Element d = new Element(12);
		Element e = new Element(3);
		Element f = new Element(d, e, 14);
		
		Element racine = new Element(c, f, 5);
		
		System.out.println("Profondeur: "+racine.getProfondeur());
		System.out.println("Max: "+racine.getMax());
		System.out.println("Arbre: "+racine);
		
		System.out.println("nombre Noeud: "+Element.getNombreNoeudCree());
	}
}
