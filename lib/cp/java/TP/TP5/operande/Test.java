package correction.tp5.operande;

public class Test {

	public static void main(String[] args) {
		
		Operande six = new Operande(6);
		Operande seven = new Operande(7);
		Operande seven2 = new Operande(7);
		Operande eight = new Operande(8);
		
		Operateur mult1 = new Multiplication(six, seven);
		Operateur add1 = new Addition(seven2, eight);
		Operateur add2 = new Addition(mult1, add1);
		
		System.out.println(add2);
		
		
	}

}
