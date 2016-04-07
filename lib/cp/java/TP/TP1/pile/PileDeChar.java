package correction.tp1.pile;

public class PileDeChar {
	public final static int TAILLE_MAX = 100;

	private char[] pile;
	private int compteur;

	public PileDeChar(){
		pile = new char[PileDeChar.TAILLE_MAX];
		this.compteur = 0;
	}

	public boolean estVide(){
		return compteur == 0;
	}

	public boolean estPleine(){
		return compteur == PileDeChar.TAILLE_MAX;
	}

	public boolean empiler(char c){
		if(!estPleine()){
			pile[compteur]=c;
			compteur++;
			return true;
		}else{
			return false;
		}
	}

	public char depiler(){
		if(!estVide()){
			compteur--;
			return pile[compteur];
		}else{
			return '\0';
		}
	}

	public static class Test {

		public static String miroir(String s){
			int i=0;
			int taille = s.length();
			PileDeChar pile = new PileDeChar();
			char[] tab = new char[taille];
			
			for(i=0; i< s.length(); i++){
				pile.empiler(s.charAt(i));
			}

			for(i=0; i< s.length(); i++){
				tab[i] = pile.depiler();
			}

			return new String(tab);
		}

		public static void main(String[] argv){
			PileDeChar p = new PileDeChar();
			System.out.println(miroir("Hello World"));
		}

	}

}
