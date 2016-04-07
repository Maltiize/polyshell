package correction.tp3.polyNombre;

public class PolyFloat extends PolyNombre {

	private float f;
	
	public PolyFloat(float f){
		this.f = f;
	}
	
	@Override
	public int intValue() {
		return (int)f;
	}

	@Override
	public float floatValue() {
		return (float)f;
	}

	@Override
	public double doubleValue() {
		return (double)f;
	}

	@Override
	public String toString() {
		return String.valueOf(f);
	}
}
