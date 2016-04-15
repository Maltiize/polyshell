#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h> // Pour les arguments


int rm(int argc, char *argv[])
{

	//Partie getopt
    char opt; // Pour stocker les options passé en paramètre 1 à 1
    char * options = "hc" ; // Les options disponibles

    int help = 0; //option h
    int c = 0; // option c : Demande une confirmation avant de supprimer, faire attention peut etre dangereux si on ne l'uilise pas.
    //int d = 0; // option d : Permet de supprimer tout les fichiers d'un dossier. Faire attention peut etre dangereux.
    //int n = 0; //suppression normal mais mis en arg pour pas tout le temps suppr c'est relou

	// Récupérer les options
    while ((opt = getopt (argc, argv, options)) != -1)
    {
        switch(opt)
        {
            case '?':
                printf("Un des paramètres n'est pas reconnu. Utiliser -h pour obtenir de l'aide. \n");
                return 1;
                break;
            case 'h':
                help = 1;
                break;
            case 'c':
                c = 1;
                break;
            //case 'd':
              //  d = 1;
                //break;
            default:
                printf("Une erreur est survenu lors de la saisie des paramètres. \n");
                return 1;
                break;
        }
    }


    if (help == 1)
    {
        printf("Pour utiliser la fonction rm taper : rm [-options] [nom_du_fichier] [nom_du_fichier_2] ...\n");
        printf("Echo : Supprime des fichiers. \n");
        printf("\t -h : Affiche l'aide. \n");
        printf("\t -c : Demande la confirmation avant de supprimer. \n");
        printf("\t -d : Pour supprimer un dossier et tout ses fichiers. \n");
        return 0;
    }

    else if (c == 1)	//confirmation
    {
        printf("Souhaitez vous vraiment supprimer ce fichier ? Entrez oui pour supprimer et non pour annuler.\n");
		char yon[10];
        char valide[]="oui\n";
		fgets(yon, 10, stdin);
        printf("[%s]\n",yon );

		if(strcmp(yon,valide)==0)
		{
			printf("Vous avez selectionnez oui. Suppresion.\n");
    		for(int i=1;i<argc;i++)
			{
    		    remove(argv[i]);
    		}
    		return 0;
		}
		else
		{
			printf("Vous avez selectionnez non. Annulation de la suppression.\n");
            return 1;
		}
    }else{  //Sinon il n'y a pas d'option alors on suprime le fic
		for(int i=1;i<argc;i++)
		{
		    remove(argv[i]);
		}
		printf("Suppresion effectué.\n");
		return 0;
	}

	return 0;
}


int main(int argc, char *argv[])
{
    rm(argc, argv);
    return 0;
}
