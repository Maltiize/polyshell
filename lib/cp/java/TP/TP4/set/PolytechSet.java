package correction.tp4.set;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.Set;
import java.util.Spliterator;


public class PolytechSet<T> implements Set<T>, Cloneable,Comparable {

	private ArrayList<T> tab;
	
	public PolytechSet(int capacity){
		this.tab = new ArrayList<T>(capacity);
	}
	
	public PolytechSet(){
		this(10);
	}
	
	private boolean isContained(T o){
		for(Object current : this.tab){
			if(o.equals(current)){
				return true;
			}
		}	
		return false;
	}
	
	@Override
	public boolean add(T arg0) {
		
		if(!isContained(arg0)){
			this.tab.add(arg0);
			return true;
		}else{
			return false;
		}
	}

	@Override
	public boolean addAll(Collection<? extends T> arg0) {
		
		boolean atLeastOne = false;
		
		for(T current : arg0){
			if(this.add(current)){
				atLeastOne = true;
			}
		}
		
		return atLeastOne;
	}

	@Override
	public void clear() {
		this.tab.clear();
		
	}

	@Override
	public boolean contains(Object arg0) {
		return this.tab.contains(arg0);
	}

	@Override
	public boolean containsAll(Collection<?> arg0) {
		return this.tab.containsAll(arg0);
	}

	@Override
	public boolean isEmpty() {
		return this.tab.isEmpty();
	}

	@Override
	public Iterator<T> iterator() {
		return this.tab.iterator();
	}

	@Override
	public boolean remove(Object arg0) {
		return this.tab.remove(arg0);
	}

	@Override
	public boolean removeAll(Collection<?> arg0) {
		return this.tab.removeAll(arg0);
	}

	@Override
	public boolean retainAll(Collection<?> arg0) {
		return this.tab.retainAll(arg0);
	}

	@Override
	public int size() {
		return this.tab.size();
	}

	@Override
	public Object[] toArray() {
		return this.tab.toArray();
	}

	@Override
	public <T> T[] toArray(T[] arg0) {
		return this.tab.toArray(arg0);
	}

	@SuppressWarnings("unchecked")
	@Override
	public Object clone(){
		PolytechSet<T> copy = null;
				
		try {
			copy = (PolytechSet<T>) super.clone();
			
		} catch (CloneNotSupportedException e) {
		
		}
		
		copy.tab = (ArrayList<T>)this.tab.clone();
		
		
		return copy;
	}

	@Override
	public int compareTo(Object arg0) {
	
		@SuppressWarnings("unchecked")
		PolytechSet<T> arg = (PolytechSet<T>) arg0;
		
		if(this.tab.size() > arg.tab.size()){
			return 1;
		}
		
		if(this.tab.size() < arg.tab.size()){
			return -1;
		}
		
		return 0;
	}
	
	@Override
	public String toString() {
		return this.tab.toString();
	}
	
	@Override
	public Spliterator<T> spliterator() {
		return null;
	}
	
	public static class Test {
		public static void main(String[] args) {
			
			Set<Personne> set1 = new PolytechSet<Personne>();
			Set<Personne> set2 = new PolytechSet<Personne>();
			Set<Personne> set3;
			
			Personne p1 = new Personne("Antoine", "Pigeau", "3 rue La Mouche");
			Personne p2 = new Personne("Antoine", "Pigeau", "3 rue La Mouche");
			Personne p3 = new Personne("Arthur", "Pigeau", "3 rue La Mouche");
			Personne p4 = new Personne("Stéphanie", "Pigeau", "3 rue La Mouche");
			
			set1.add(p1);
			set1.add(p2);
			set1.add(p3);
			set1.add(p4);
			
			System.out.println(set1);
			
			set2.add(p1);
			set2.add(p3);
			
			System.out.println(set2);
			
			set3 = (PolytechSet<Personne>)((PolytechSet)set1).clone();
			
			System.out.println(set3);
			
			p1.setNom("Mc Colin");
			
			System.out.println(set1);
			System.out.println(set3);
			
			
			System.out.println("Comparable:"+((PolytechSet<Personne>)set1).compareTo(set2));
			
		}
	}
	
}
