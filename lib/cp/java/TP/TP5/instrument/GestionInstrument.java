package correction.tp5.instrument;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.HashSet;
import java.util.Set;

public class GestionInstrument {

	private Set<Instrument> sets;
	
	public GestionInstrument() {
		this.sets = new HashSet<>();
	}
	
	public boolean addInstrument(Instrument instrument) throws ExceptionAlreadyAdded {
		
		boolean added = this.sets.add(instrument);
		
		if(!added){
			throw new ExceptionAlreadyAdded();
		}
		
		return added;
	}
	
	public boolean remove(Instrument instrument){
		return this.sets.remove(instrument);
	}
	
	public void afficheInstrument(){
		System.out.println(this.sets);
	}
	
	public void load(){
		
		try(ObjectInputStream read = new ObjectInputStream(new FileInputStream("save.obj"));){
			
			int nbrInstrument = read.readInt();
			for(int i = 0; i < nbrInstrument; i++){
				this.sets.add((Instrument)read.readObject());
			}
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
	}
	
	public void save(){
		
		try(ObjectOutputStream write = new ObjectOutputStream(new FileOutputStream("save.obj"));){
			
			write.writeInt(this.sets.size());
			for(Instrument instrument : this.sets){
				write.writeObject(instrument);
			}
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void clear(){
		this.sets.clear();
	}

}
