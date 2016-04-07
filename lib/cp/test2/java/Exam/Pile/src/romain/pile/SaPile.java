package romain.pile;

import java.util.EmptyStackException;

public class SaPile implements pile{
	  private Object[] items;
	  private int top=0;
	  private int max=100;
	  public SaPile(){items = new Object[max];}
	  public Object empiler(Object item){
	  if (this.estPleine())
	      throw new EmptyStackException();      
	  items[top++] = item;
	  return item;
	  }
	  public synchronized Object dépiler(){
		    Object item = null;
		    if (this.estVide())
		      throw new EmptyStackException();
		    item = items[--top];
		        return item;
		  } 
		  public boolean estVide(){
		    return (top == 0);
		  }
		 public boolean estPleine(){
		    return (top == max -1);
		  }
		  protected void finalize() throws Throwable {
		    items = null; super.finalize();
		  }
		}