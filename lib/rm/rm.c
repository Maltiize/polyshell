#include <stdio.h>
#include <stdlib.h>


int rm(int argc, char *argv[])
{

	//Partie getopt
    char opt; // Pour stocker les options passé en paramètre 1 à 1
    char * options = "hcd" ; // Les options disponibles

    int help = 0; //option h
    int c = 0; // option c : Demande une confirmation avant de supprimer, faire attention peut etre dangereux si on ne l'uilise pas.
    int d = 0; // option d : Permet de supprimer un dossier. Faire attention peut etre dangereux.

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
            case 'd':
                d = 1;
                break;
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

    if (c == 1)	//confirmation
    {
        printf("Souhaitez vous vraiment supprimer ce fichier ? Entrez 1 pour supprimer et 0 pour annuler.\n");
		int yon = 0;
		scanf("%s", yon);

		if(yon == 1)					// JE COMPRENDS PAS POURQUOI LORSQUE JE MET 1 IL RENTRE PAS DEDANS ??? 
		{
			printf("Vous avez selectionnez 1.\n");
    		for(int i=1;i<argc;i++)
			{
    		    remove(argv[i]);
    		}
    		return 0;
		}
		else if(yon == 0)
		{
			printf("Vous avez selectionnez 0. Annulation de la suppression.\n");
		}
    }



	if (d == 1)	//suppression normal
	{
		//fonction de supp
		for(int i=1;i<argc;i++)
		{
		    remove(argv[i]);
		}
		return 0;
	}
}


int main(int argc, char *argv[])
{
    rm(argc, argv);
}