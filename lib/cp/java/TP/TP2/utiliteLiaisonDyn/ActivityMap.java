package correction.tp2.utiliteLiaisonDyn;

public abstract class ActivityMap {
	
	public ActivityMap(){

		preparerImages();

		chargerVue();  
		
		recupererLocalisation();
		
		chargerAction();
	}

	protected abstract void chargerVue();
	protected abstract void chargerAction();
	
	private void recupererLocalisation() {
		System.out.println("recupererLocalisation()");
	}
	private void preparerImages() {
		System.out.println("preparerImages()");
	}
}
