package correction.tp1.garbageCollector;

public class ObjetToDelete {

	public static int nbObjet = 0;
	
	private int i;
	
	public ObjetToDelete(){
		i = nbObjet++;
	}
	
	@Override
	protected void finalize() throws Throwable {
		System.out.println("destuction objet:"+i);
	}
}
