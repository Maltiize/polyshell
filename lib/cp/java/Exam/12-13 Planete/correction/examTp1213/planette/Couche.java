package correction.examTp1213.planette;

public class Couche extends Planete{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private Planete planete;
	
	public Couche(Planete planette, String nom, float densite, int profondeurMin, int profondeurMax){
		super(nom, densite, profondeurMin, profondeurMax);
		this.planete = planette;
	}

	@Override
	public String toString() {
		return "["+super.toString()+this.planete+"]";
	}
	
	@Override
	public int radiusPlanete() {
		return this.planete.radiusPlanete();
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result
				+ ((planete == null) ? 0 : planete.hashCode() + super.hashCode());
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
		
		Couche other = (Couche) obj;
		if(!super.equals(other)){
			return false; 
		}
		
		if (planete == null) {
			if (other.planete != null)
				return false;
		}else if (!planete.equals(other.planete)){
			return false;
		}
		
		return true;
	}

	@Override
	protected Object clone() throws CloneNotSupportedException {
		
		Couche clone = (Couche)super.clone();
		clone.planete = (Planete)this.planete.clone();
		
		return clone;
	}
	
	
}
