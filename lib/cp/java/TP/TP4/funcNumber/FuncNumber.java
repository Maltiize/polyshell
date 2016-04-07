package correction.tp4.funcNumber;


public class FuncNumber<T extends Number> {
	private T n;
	
	public FuncNumber(T l){
		this.n = l;
	}
	
	public Long sum(){
		Long l = new Long(n.longValue());
		return FuncNumber.sum(l);
	}
	
	public static Long sum(Long l){
		if(l.longValue() == 0){
			return new Long(0);
		}else{
			Long l2 = new Long(l.longValue()-1);
			return new Long( FuncNumber.sum(l2) + l.longValue() );
		}
	}
	
	public static class Test{
		public static void main(String[] argv){
			FuncNumber<Integer> n = new FuncNumber<Integer>(new Integer(3));
			System.out.println(n.sum().longValue());
		}
	}
	 
}
