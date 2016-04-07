package correction.examTp1213.planette;

import java.io.File;

public class Test {
	public static void main(String[] args) {
		
		Planete planeteClone = null;
		Planete earth = FactoryPlanete.getEarth();
		Planete earth2 = FactoryPlanete.getEarth2();
		Planete moon = FactoryPlanete.getMoon();
		Planete mars = FactoryPlanete.getMars();
		Planete mars2 = FactoryPlanete.getMars2();
		
		System.out.println(earth);
		System.out.println(earth.radiusPlanete());
		
		GestionPlanete gestionPlanete = new GestionPlanete();
		System.out.println(gestionPlanete.addPlanete(earth));
		System.out.println(gestionPlanete.addPlanete(earth));
		try {
			System.out.println(gestionPlanete.addPlanete((Planete)earth.clone()));
		} catch (CloneNotSupportedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println(gestionPlanete.addPlanete(moon));
		System.out.println(gestionPlanete.addPlanete(mars));
		System.out.println(gestionPlanete.addPlanete(earth2));
		
		System.out.println(earth.equals(mars2));
		
		/* System.out.println(earth.hashCode());
		System.out.println(earth2.hashCode());
		
		System.out.println(earth.equals(earth2));
		
		System.out.println(gestionPlanete);
		
		try {
			planeteClone = (Planete)earth.clone();
			System.out.println(planeteClone);
			System.out.println(earth);
			System.out.println(earth.equals(planeteClone));
		} catch (CloneNotSupportedException e) {
			e.printStackTrace();
		} */
		
		File file = new File("ExamTP2012-2013");
		gestionPlanete.savePlanete(file);
		
		gestionPlanete.loadPlanete(file);
		
		System.out.println(gestionPlanete);
		
		gestionPlanete.afficheTrier();
		
	}
}
