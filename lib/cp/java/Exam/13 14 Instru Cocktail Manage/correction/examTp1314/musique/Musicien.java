package correction.examTp1314.musique;

import java.util.HashSet;
import java.util.Set;

/**
 * classe musicien
 * 
 * @author pigeau-a
 *
 */
public class Musicien {

	/**
	 * nom du musicien
	 */
	private String nom;
	private String prenom;
	private Set<Instrument> instrument;
	
	/**
	 * 
	 * @param nom du musicien
	 * @param prenom du musicien
	 * @param age du musicien
	 * @param instrument joué par le musicien
	 */
	public Musicien(String nom, String prenom, Instrument... instrument ) {
		super();
		this.nom = nom;
		this.prenom = prenom;
		this.instrument = new HashSet<>();
		
		for(Instrument instr: instrument){
			this.instrument.add(instr);
		}
		
	}

	public String getNom() {
		return nom;
	}

	public void setNom(String nom) {
		this.nom = nom;
	}

	public String getPrenom() {
		return prenom;
	}

	public void setPrenom(String prenom) {
		this.prenom = prenom;
	}

	public Set<Instrument> getInstrument() {
		return instrument;
	}

	public void setInstrument(Set<Instrument> instrument) {
		this.instrument = instrument;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result
				+ ((instrument == null) ? 0 : instrument.hashCode());
		result = prime * result + ((nom == null) ? 0 : nom.hashCode());
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
		Musicien other = (Musicien) obj;
		if (instrument == null) {
			if (other.instrument != null)
				return false;
		} else if (!instrument.equals(other.instrument))
			return false;
		if (nom == null) {
			if (other.nom != null)
				return false;
		} else if (!nom.equals(other.nom))
			return false;
		if (prenom == null) {
			if (other.prenom != null)
				return false;
		} else if (!prenom.equals(other.prenom))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "Musicien [nom=" + nom + ", prenom=" + prenom + ", instrument="
				+ instrument + "]";
	}	
	
	
}
