package correction.tp5.instrument;

import java.io.Serializable;

public abstract class Instrument implements Cloneable, Serializable {

	private Categorie categorie;
	private String type;
	private String reference;
	
	public Instrument(Categorie categorie, String type, int number) {
		this.categorie = categorie;
		this.type = type;
		this.reference = this.type + "-" + number;
		
	}

	public int getPrix() {
		return categorie.getPrix();
	}
		
	public Categorie getCategorie() {
		return categorie;
	}

	public String getReference() {
		return reference;
	}

	public void setReference(String reference) {
		this.reference = reference;
	}

	@Override
	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result
				+ ((categorie == null) ? 0 : categorie.hashCode());
		result = prime * result
				+ ((reference == null) ? 0 : reference.hashCode());
		result = prime * result + ((type == null) ? 0 : type.hashCode());
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
		Instrument other = (Instrument) obj;
		if (categorie != other.categorie)
			return false;
		if (reference == null) {
			if (other.reference != null)
				return false;
		} else if (!reference.equals(other.reference))
			return false;
		if (type == null) {
			if (other.type != null)
				return false;
		} else if (!type.equals(other.type))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "Instrument [categorie=" + categorie + ", type=" + type
				+ ", reference=" + reference + "]";
	}
	
}
