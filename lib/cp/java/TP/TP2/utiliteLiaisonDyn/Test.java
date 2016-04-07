package correction.tp2.utiliteLiaisonDyn;

public class Test {
	public static void main(String[] args) {
		
		ActivityMapOld activityAOld = new ActivityMapOld(true);
		
		System.out.println("");
		
		ActivityMap parcours = new ActivityModeParcours();
		
		System.out.println("");
		
		ActivityMap localisation = new ActivityModeLocalisation();
	}
}
