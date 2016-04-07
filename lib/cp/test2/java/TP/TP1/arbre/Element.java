package correction.tp1.arbre;

public class Element {
	
	private static int nombreNoeud = 0;
	
	public static int getMaxRec(Element element){
		int max = 0;
		
		if(element != null){
			max = Math.max(element.value, Math.max(getMaxRec(element.left), getMaxRec(element.right)));
		}
		
		return max;
	}
	
	public static int getProfondeurRec(Element element) {
		
		int profondeur = 0;
		
		if(element != null){
			profondeur = 1 + Math.max(getProfondeurRec(element.left), getProfondeurRec(element.right));
		}
		
		return profondeur;
	}
	
	public static int getNombreNoeudCree(){
		return nombreNoeud;
	}
	
	private Element left;
	private Element right;
	private int value;
	
	public Element(Element left, Element right, int value) {
		super();
		this.left = left;
		this.right = right;
		this.value = value;
		
		nombreNoeud++;
	}
	
	public Element(int value){
		this(null, null, value);
	}
	
	public int getMax(){
		return getMaxRec(this);
	}
	
	public int getProfondeur(){
		return getProfondeurRec(this);
	}
	
	@Override
	public String toString() {
		
		StringBuilder stringBuilder = new StringBuilder();
		
		stringBuilder.append(this.value);
		stringBuilder.append(" [");
		stringBuilder.append(this.left);
		stringBuilder.append(", ");
		stringBuilder.append(this.right);
		stringBuilder.append("] ");
		
		return stringBuilder.toString();
	}
	
}
