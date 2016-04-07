package correction.tp1.number;

import java.util.ArrayList;
import java.util.List;

public class GestionMesure {
	private List<Double> nombres;

	public GestionMesure() {
		this(null);
	}
	
	public GestionMesure(List<Number> list) {
		this.nombres = new ArrayList<>();
		this.addAll(list);
	}

	public boolean add(Integer i){
		return nombres.add(i.doubleValue());
	}

	public boolean add(Float f){
		return nombres.add(f.doubleValue());
	}

	public boolean add(Double d){
		return nombres.add(d);
	}

	public void addAll(List<Number> l){

		if(l != null){
			for(Number n: l){
				this.nombres.add(n.doubleValue());
			}
		}
	}
	
	public double getEcartType(){
		return Math.sqrt(this.getVariance());
	}
	
	public double getVariance(){
		
		if(this.nombres.isEmpty()){
			return 0.0;
		}
		
		double moyenneDesCarres =0.0;
		
		for(Double d : this.nombres){
			moyenneDesCarres += d*d;
		}
		moyenneDesCarres = moyenneDesCarres/this.nombres.size();
		
		double moyenne = this.getMoyenne();
				
		
		return moyenneDesCarres - moyenne*moyenne;
	}
	
	public double getMedianne(){
		
		if(this.nombres.isEmpty()){
			return 0.0;
		}
		
		int milieu = this.nombres.size() / 2;
		
		return this.nombres.get(milieu);
	}
	

	public double getMoyenne(){
		
		if(this.nombres.isEmpty()){
			return 0.0;
		}
		
		double somme = 0.0;
		
		for(Double d: this.nombres){
			somme += d;
		}
		
		return somme / this.nombres.size();
	}
}
