package correction.tp3.pile;

public class StackableStackDefault extends StackableStack {

	public StackableStackDefault(Stack s) {
		super(s);
		// TODO Auto-generated constructor stub
	}

	@Override
	public boolean isEmpty() {
		// TODO Auto-generated method stub
		return this.s.isEmpty();
	}

	@Override
	public Object pop() {
		// TODO Auto-generated method stub
		return this.s.pop();
	}

	@Override
	public void push(Object o) {
		// TODO Auto-generated method stub
		this.s.push(o);
	}

	@Override
	public Object top() {
		// TODO Auto-generated method stub
		return this.s.top();
	}
	
	@Override
	public String toString() {
		// TODO Auto-generated method stub
		return this.s.toString();
	}
	
}
