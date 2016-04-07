package correction.examTp1213.planette;

import java.io.IOException;
import java.io.Serializable;

public abstract class Planete implements Comparable<Planete>, Cloneable, Serializable{

	/**
	 * 
	 */
	private static final long serialVersionUID = -2306096784991775220L;
	
	protected String nomCouche;
	protected float densite;
	protected int profondeurMin;
	protected int profondeurMax;

	public Planete(String nomCouche, float densite, int profondeurMin, int profondeurMax){

		this.nomCouche = nomCouche;
		this.densite = densite;
		this.profondeurMin = profondeurMin;
		this.profondeurMax = profondeurMax;
	}

	public String toString() {
		return "["+this.nomCouche+", "+this.densite+", "+this.profondeurMin+", "+this.profondeurMax+"]";
	}

	public int radiusPlanete() {
		return this.profondeurMax;
	}


	public String getNomCouche() {
		return nomCouche;
	}

	public float getDensite() {
		return densite;
	}

	public int getProfondeurMin() {
		return profondeurMin;
	}

	public int getProfondeurMax() {
		return profondeurMax;
	}

	@Override
	public int compareTo(Planete o) {
		if(this.radiusPlanete() < o.radiusPlanete()){
			return -1;
		}

		if(this.radiusPlanete() == o.radiusPlanete()){
			return 0;
		}
		return 1;
	}

	@Override
	protected Object clone() throws CloneNotSupportedException {
		return super.clone();
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + Float.floatToIntBits(densite);
		result = prime * result
				+ ((nomCouche == null) ? 0 : nomCouche.hashCode());
		result = prime * result + profondeurMax;
		result = prime * result + profondeurMin;
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
		Planete other = (Planete) obj;
		if (Float.floatToIntBits(densite) != Float
				.floatToIntBits(other.densite))
			return false;
		if (nomCouche == null) {
			if (other.nomCouche != null)
				return false;
		} else if (!nomCouche.equals(other.nomCouche))
			return false;
		if (profondeurMax != other.profondeurMax)
			return false;
		if (profondeurMin != other.profondeurMin)
			return false;
		return true;
	}

	private void writeObject(java.io.ObjectOutputStream out)
			throws IOException{
		out.defaultWriteObject();
	}
	private void readObject(java.io.ObjectInputStream in)
			throws IOException, ClassNotFoundException{
		in.defaultReadObject();
	}

}
