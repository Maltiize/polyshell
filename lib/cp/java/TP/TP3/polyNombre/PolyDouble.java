package correction.tp3.polyNombre;

public class PolyDouble extends PolyNombre {

	private double d;
	
	public PolyDouble(double d){
		this.d = d;
	}
	
	@Override
	public int intValue() {
		// TODO Auto-generated method stub
		return (int)d;
	}

	@Override
	public float floatValue() {
		// TODO Auto-generated method stub
		return (float)d;
	}

	@Override
	public double doubleValue() {
		// TODO Auto-generated method stub
		return d;
	}

	@Override
	public String toString() {
		// TODO Auto-generated method stub
		return String.valueOf(d);
	}
}
