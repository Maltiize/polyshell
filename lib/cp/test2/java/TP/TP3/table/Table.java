package correction.tp3.table;

import java.util.Iterator;

public class Table<T> {
	protected int compteur;
	protected Object[] tab;
	protected int tailleMax;
	
	public Table(int tailleMax){
		this.compteur = 0;
		this.tailleMax = tailleMax;
		this.tab = new Object[tailleMax];
	}
	
	private boolean estPlein(){
		return this.compteur == tailleMax;
	}
	
	public boolean add(T o){
		if(!estPlein()){
			this.tab[this.compteur] = o;
			this.compteur++;
			return true;
		}else{
			return false;
		}
	}
	
	public int getSize(){
		return this.compteur+1;
	}
	
	public Iterator<T> getIterator(){
		return this.new TableIterator();
	}
	
	/**
	 * the iterator of table
	 * @author antoine
	 *
	 */
	protected class TableIterator implements Iterator<T> {

		protected int indice;
		
		public TableIterator(){
			this.indice = 0;
		}
		
		@Override
		public boolean hasNext() {
			// TODO Auto-generated method stub
			return this.indice != compteur;
		}

		@Override 
		public T next() {
			
			@SuppressWarnings("unchecked")
			T o = (T)tab[this.indice]; 
			this.indice++;
			return o;
		}

		@Override
		public void remove() {
			throw new UnsupportedOperationException();
		}

	}
}
