package romain.pile;

class Main{
    public static void faire(pile p){  
        for(int i=0; i<10; i++)
            p.empiler(new Integer(i*i));
        while(! p.estVide())
            System.out.println(p.dépiler());
    }   
    public static void main(String[] args){
        pile p=new Mapile();
        faire(p);
        p=new SaPile();
        faire(p);
    }
}
