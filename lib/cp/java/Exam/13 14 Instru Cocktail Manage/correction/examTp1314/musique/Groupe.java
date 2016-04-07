package correction.examTp1314.musique;

import java.util.HashSet;
import java.util.Set;

public class Groupe {

	private Set<Musicien> setMusicien;
	private Set<Album> setAlbum;
	private String nom;
	private Style style;

	public Groupe(String nom, Style style, Set<Musicien> setMusicien) throws EmptyPolyBandException {
		this(null, nom, style, setMusicien);
	}

	public Groupe(Set<Album> setAlbum, String nom, Style style, Set<Musicien> setMusicien) throws EmptyPolyBandException {
		super();

		this.setMusicien = new HashSet<>();

		if(setMusicien != null){
			for(Musicien mus: setMusicien){
				this.setMusicien.add(mus);
			}
		}else{
			throw new EmptyPolyBandException();
		}

		this.setAlbum = new HashSet<>();
		
		if(setAlbum != null){
			for(Album alb: setAlbum){
				this.setAlbum.add(alb);
			}
		}
		
		this.nom = nom;
		this.style = style;
	}


	public Set<Musicien> getSetMusicien() {
		return setMusicien;
	}


	public void setSetMusicien(Set<Musicien> setMusicien) {
		this.setMusicien = setMusicien;
	}


	public Set<Album> getSetAlbum() {
		return setAlbum;
	}


	public void setSetAlbum(Set<Album> setAlbum) {
		this.setAlbum = setAlbum;
	}


	public String getNom() {
		return nom;
	}


	public void setNom(String nom) {
		this.nom = nom;
	}


	public Style getStyle() {
		return style;
	}


	public void setStyle(Style style) {
		this.style = style;
	}



	@Override
	public String toString() {
		return "Groupe [setMusicien=" + setMusicien + ", setAlbum=" + setAlbum
				+ ", nom=" + nom + ", style=" + style + "]";
	}



	public static class Test {
		public static void main(String[] args) {

			Musicien kurt = new Musicien("Cobain", "Kurt", Instrument.Guitare);
			Musicien krist = new Musicien("Novo", "Krist", Instrument.Basse);
			Musicien dave = new Musicien("Grohl", "Dave", Instrument.Batterie);

			Set<Musicien> setMusicien = new HashSet<>();
			setMusicien.add(kurt);
			setMusicien.add(krist);
			setMusicien.add(dave);
			
			Album nevermind = new Album("Nevermind", 1991);
			Album inUtero = new Album("In Utero", 1993);

			Set<Album> setAlbum = new HashSet<>();
			setAlbum.add(nevermind);
			setAlbum.add(inUtero);
			
			Groupe nirvana = null;
			
			
			try{
				nirvana = new Groupe(setAlbum, "Nirvana", Style.Rock, setMusicien);
				System.out.println(nirvana);
				
				new Groupe(null, "test", Style.HardRock, null);
				
			}catch(EmptyPolyBandException e){
				System.out.println(e);
			}

			
		}
	}

}
