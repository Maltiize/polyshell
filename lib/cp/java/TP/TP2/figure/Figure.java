package correction.tp2.figure;

public abstract class Figure {
	
	protected String description;
	
	public Figure(String description){
		this.description = description;
	}

	
	@Override
	public String toString() {
		return this.description;
	}
}
