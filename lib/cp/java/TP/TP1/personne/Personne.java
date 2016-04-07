package correction.tp1.personne;

public class Personne implements Comparable<Personne> {
	private String nom;
	private String prenom;
	private int age;
	private Personne pere;
	private Personne mere;
	
	public Personne(String nom, String prenom, int age, Personne pere, Personne mere){
		this.nom = nom;
		this.prenom = prenom;
		this.age = age;
		this.pere = pere;
		this.mere = mere;
	}
	
	public Personne(String nom, String prenom, int age){
		this(nom, prenom, age, null, null);
	}
	
	public Personne(){
		this("Doe", "John", 25, null, null);
	}
	
	public String getNom() {
		return nom;
	}
	public String getPrenom() {
		return prenom;
	}
	public int getAge() {
		return age;
	}

	@Override
	public String toString() {
		return "Personne [nom=" + nom + ", prenom=" + prenom + ", age=" + age
				+ ", pere=" + pere + ", mere=" + mere + "]";
	}

	@Override
	public int compareTo(Personne arg0) {
		
		if(arg0 == null){
			return 1;
		}
		
		int cmpNom = this.nom.compareTo(arg0.nom);
		
		if(cmpNom != 0){
			return cmpNom;
		}else{
			return this.prenom.compareTo(arg0.prenom);
		}
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + age;
		result = prime * result + ((mere == null) ? 0 : mere.hashCode());
		result = prime * result + ((nom == null) ? 0 : nom.hashCode());
		result = prime * result + ((pere == null) ? 0 : pere.hashCode());
		result = prime * result + ((prenom == null) ? 0 : prenom.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Personne other = (Personne) obj;
		if (age != other.age)
			return false;
		if (mere == null) {
			if (other.mere != null)
				return false;
		} else if (!mere.equals(other.mere))
			return false;
		if (nom == null) {
			if (other.nom != null)
				return false;
		} else if (!nom.equals(other.nom))
			return false;
		if (pere == null) {
			if (other.pere != null)
				return false;
		} else if (!pere.equals(other.pere))
			return false;
		if (prenom == null) {
			if (other.prenom != null)
				return false;
		} else if (!prenom.equals(other.prenom))
			return false;
		return true;
	}
	
	
	
}
