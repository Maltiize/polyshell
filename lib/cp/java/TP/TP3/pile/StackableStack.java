package correction.tp3.pile;

public abstract class StackableStack implements Stack {
	
	protected Stack s;
	
	public StackableStack(Stack s){
		this.s = s;
	}
	
	void pushAll(Stack a){
		Object o = a.pop();
		while (o != null){
			this.s.push(o);
			o = a.pop();
			System.out.println("test:"+o);
		}
	}
}
