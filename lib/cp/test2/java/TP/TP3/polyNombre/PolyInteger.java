package correction.tp3.polyNombre;

public class PolyInteger extends PolyNombre{
	
	private int i;
	
	public PolyInteger(int i){
		this.i = i;
	}
	
	@Override
	public int intValue() {
		return (int)i;
	}

	@Override
	public float floatValue() {
		return (float)i;
	}

	@Override
	public double doubleValue() {
		return i;
	}
	
	@Override
	public String toString() {
		// TODO Auto-generated method stub
		return String.valueOf(i);
	}
}
