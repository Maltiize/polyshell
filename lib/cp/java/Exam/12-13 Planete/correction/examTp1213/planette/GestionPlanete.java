package correction.examTp1213.planette;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class GestionPlanete {
	private Set<Planete> planeteSet;
	
	public GestionPlanete(){
		this.planeteSet = new HashSet<>();
	}
	
	public boolean addPlanete(Planete planete){
		return this.planeteSet.add(planete);
	}
	
	public boolean removePlanete(Planete planete){
		return this.planeteSet.remove(planete);
	}
	
	@Override
	public String toString(){
		StringBuffer buff = new StringBuffer();
		for(Planete current: this.planeteSet){
			buff.append("[");
			buff.append(current);
			buff.append("]");
		}
		
		return buff.toString();
	}
	
	public void loadPlanete(File file){
		
		FileInputStream fileInputStream = null;
		ObjectInputStream in = null;
		
		try {
			fileInputStream = new FileInputStream(file);
			in = new ObjectInputStream(fileInputStream);
			this.planeteSet = (HashSet<Planete>)in.readObject();
		
		} catch (FileNotFoundException e) {
			
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	

	public void savePlanete(File file){
		
		FileOutputStream fileOutputStream = null;
		ObjectOutputStream out = null;
		
		try {
			fileOutputStream = new FileOutputStream(file);
			out = new ObjectOutputStream(fileOutputStream);
			out.writeObject(this.planeteSet);
		
		} catch (FileNotFoundException e) {
			
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void afficheTrier(){
		List<Planete> list = new ArrayList<>();
		list.addAll(this.planeteSet);
		Collections.sort(list);
		
		for(Planete p: list){
			System.out.println(p);
		}
	}
}
