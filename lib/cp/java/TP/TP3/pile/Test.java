package correction.tp3.pile;

public class Test {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Stack a = new ArrayStack();
		Stack v = new VectorStack();
		v.push("ab");
		v.push("cd");
		System.out.println(a.toString());
		
		
		
		StackableStack s = new StackableStackDefault(a);
		s.push("ef");
		s.push("gh");
		//b.push("ij");
		
		System.out.println(a.toString());
		
		s.pushAll(v);
		System.out.println("Result:"+s.toString());
	}

}
