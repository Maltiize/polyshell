package correction.tp2.utiliteLiaisonDyn;

public class ActivityMapOld {


	public ActivityMapOld(Boolean modeParcours){

		recupererLocalisation();

		if(modeParcours){
			chargerVueModeParcours();  
		}else{
			chargerVueModeLocalisation();
		}

		preparerImages();

		if(modeParcours){
			chargerActionModeParcours();  
		}else{
			chargerActionModeLocalisation();
		}    
	}

	private void chargerActionModeLocalisation() {
		System.out.println("chargerActionModeLocalisation()");
	}

	private void chargerActionModeParcours() {
		System.out.println("chargerActionModeParcours()");
	}

	private void preparerImages() {
		System.out.println("preparerImages()");
	}

	private void chargerVueModeLocalisation() {
		System.out.println("chargerVueModeLocalisation()");		
	}

	private void chargerVueModeParcours() {
		System.out.println("chargerVueModeParcours()");
	}

	private void recupererLocalisation() {
		System.out.println("recupererLocalisation()");
	}

}
