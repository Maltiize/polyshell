package correction.tp3.exception;

public class Test {
	public static void main(String[] args) throws Exception {

		int x=0;
		int y=0;
		int z=0;
		
		try{

			System.out.println("Nombre d'argument:"+args.length);
			
			if(args.length != 2){
				throw new NumberArgumentException();
			}

			x = Integer.parseInt(args[0]);
			y = Integer.parseInt(args[1]);

			z = division(x, y);	
			
		}catch(NumberFormatException e){
			System.out.println("NumberFormatException: "+e.getMessage());
		}catch(ArithmeticException e){
			System.out.println("ArithmeticException: "+e.getMessage());
		}catch(NegativeNumberException e){
			System.out.println("NegativeNumberException: "+e.getMessage());
			
			x = Math.abs(x);
			y = Math.abs(y);
			
			try{
				z = division(x,y);
			}catch(ArithmeticException a){
				System.out.println("ArithmeticException: "+a.getMessage());
			}
			
		}catch(NumberArgumentException e){
			System.out.println("NumberArgumentException: "+e.getMessage());
		}
		
		System.out.println(String.valueOf(z));
	}
	
	public static int division(int x, int y) throws NegativeNumberException, ArithmeticException {
		
		if(x < 0 || y < 0){
			throw new NegativeNumberException();
		}
		
		return x/y;
	}
}
