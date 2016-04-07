package correction.tp2.utiliteLiaisonDyn;

public class ActivityModeParcours extends ActivityMap {

	public ActivityModeParcours(){
		super();
		
		System.out.println("Constructeur ModeParcours");
	}
	
	@Override
	protected void chargerVue() {
		System.out.println("chargerVueModeParcours()");	
	}

	@Override
	protected void chargerAction() {
		System.out.println("chargerActionModeParcours()");	
	}

}
