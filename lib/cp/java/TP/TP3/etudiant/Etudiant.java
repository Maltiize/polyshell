package correction.tp3.etudiant;

public class Etudiant implements Comparable<Etudiant> {

	private String nom;
	private String prenom;
	private double moyenne;
	
	public Etudiant(String nom, String prenom, double moyenne) {
		super();
		this.nom = nom;
		this.prenom = prenom;
		this.moyenne = moyenne;
	}

	public String getNom() {
		return nom;
	}

	public String getPrenom() {
		return prenom;
	}

	public double getMoyenne() {
		return moyenne;
	}

	public void setMoyenne(double moyenne) {
		this.moyenne = moyenne;
	}

	@Override
	public int compareTo(Etudiant arg0) {
		
		if(arg0 == null){
			return 1;
		}
		
		double moyenneOther = arg0.moyenne;
		
		if(this.moyenne == moyenneOther){
			return 0;
		}
		
		if(this.moyenne > moyenneOther){
			return 1;
		}else{
			return -1;
		}
	}

	@Override
	public String toString() {
		return "Etudiant [nom=" + nom + ", prenom=" + prenom + ", moyenne="
				+ moyenne + "]";
	}
	
	
	

}
