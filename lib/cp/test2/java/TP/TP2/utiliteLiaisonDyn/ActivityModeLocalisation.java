package correction.tp2.utiliteLiaisonDyn;

public class ActivityModeLocalisation extends ActivityMap {

	public ActivityModeLocalisation(){
		super();
		
		System.out.println("Constructeur ModeLocalisation");
	}
	
	@Override
	protected void chargerVue() {
		System.out.println("chargerVueModeLocalisation()");	
	}

	@Override
	protected void chargerAction() {
		System.out.println("chargerActionModeLocalisation()");	
	}

}
