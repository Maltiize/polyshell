package correction.examTp1213.planette;

public class FactoryPlanete {
	public static Planete getEarth(){
		return new Croute(new ManteauRigide(new CoeurExterne(new CoeurInterne(12.8f, 5100, 6378),9.9f, 2890, 5100),3.4f, 35, 670),2.2f, 0, 35);
	}
	
	public static Planete getEarthClone(){
		return new Croute(new ManteauRigide(new CoeurExterne(new CoeurInterne(12.8f, 5100, 6378),9.9f, 2890, 5100),3.4f, 35, 670),2.2f, 0, 35);
	}
	
	public static Planete getEarth2(){
		return new Croute(new ManteauRigide(new CoeurExterne(new CoeurInterne(12.9f, 5100, 6378),9.9f, 2890, 5100),3.4f, 35, 670),2.2f, 0, 35);
	}
	
	public static Planete getMoon(){
		return new Croute(new ManteauRigide(new CoeurExterne(new CoeurInterne(12.10f, 3000, 4000),9.9f, 2000, 3000),3.4f, 35, 2000),2.2f, 0, 35);
	}
	
	public static Planete getMars(){
		return new Croute(new ManteauRigide(new CoeurExterne(new CoeurInterne(12.11f, 3000, 8000),9.9f, 2000, 3000),3.4f, 35, 2000),2.2f, 0, 35);
	}
	
	public static Planete getMars2(){
		return new Croute(new ManteauRigide(new CoeurExterne(new CoeurExterne(new CoeurInterne(12.11f, 3000, 8000),9.9f, 2000, 3000),9.9f, 2000, 3000),3.4f, 35, 2000),2.2f, 0, 35);
	}
	
}
