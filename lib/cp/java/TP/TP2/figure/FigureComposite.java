package correction.tp2.figure;

import java.util.ArrayList;
import java.util.List;

public class FigureComposite extends Figure {
	
	private List<Figure> listFigure;
	
	public FigureComposite(Figure ...figures){
		super("Figure Composite");
		this.listFigure = new ArrayList<Figure>();
		
		for(Figure figure : figures){
			this.listFigure.add(figure);
		}
	}
	
	@Override
	public String toString() {
		StringBuffer buffer = new StringBuffer();
		buffer.append(this.description);
		buffer.append(':');
		buffer.append('[');
		for(Figure fig : this.listFigure){
			buffer.append(fig.toString());
			if(this.listFigure.indexOf(fig) != this.listFigure.size()-1){
				buffer.append(',');
			}
		}
		buffer.append(']');
		buffer.append('\n');
		return buffer.toString();
	}
	
}
