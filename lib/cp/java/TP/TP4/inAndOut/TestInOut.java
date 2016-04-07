package correction.tp4.inAndOut;

import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;


public class TestInOut {
	public static void main(String[] args) {
		long chrono = 0;
		long chrono2 = 0;
		
		try {
			FileInputStream file = new FileInputStream("Polytech.gif");
		
			chrono = java.lang.System.currentTimeMillis();
			while(file.read() != -1){}
			chrono2 = java.lang.System.currentTimeMillis();
			System.out.println(chrono2 - chrono);
			
			file.close();
			
			file = new FileInputStream("Polytech.gif");
			BufferedInputStream buff = new BufferedInputStream(file);
			chrono = java.lang.System.currentTimeMillis();
			while(buff.read() != -1){};
			chrono2 = java.lang.System.currentTimeMillis();
			System.out.println(chrono2 - chrono);
			
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
}
