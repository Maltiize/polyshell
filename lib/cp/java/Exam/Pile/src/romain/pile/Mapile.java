package romain.pile;

import java.util.EmptyStackException;
import java.util.Vector;

public class Mapile implements pile{
	  private Vector items;
	  public Mapile(){items = new Vector(10);}
	  public Object empiler(Object item){
	    items.addElement(item);
	    return item;
	  }
	  public synchronized Object dépiler(){
	    int len = items.size();
	    Object item = null;
	    if (len == 0)
	      throw new EmptyStackException();
	    item = items.elementAt(len - 1);
	    items.removeElementAt(len - 1);
	    return item;
	  }
	  public boolean estVide(){
		    return (items.size() == 0);
		  }
		  protected void finalize() throws Throwable {
		    items = null; super.finalize();
		  }
		}