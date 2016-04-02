#include <stdlib.h>
#include <stdio.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <getopt.h> // Pour les arguments

int cp(int argc, char * argv[])
{
    // Déclaration variable pour arguments

    char opt; // Pour stocker les options passé en paramètre 1 à 1
    char * options = "h" ; // Les options disponibles

    int help = 0; // -h

    char * pathSrc = NULL; // Stock le chemin source
    char * pathDest = NULL; // Stock le chemin destination

    FILE *pFileSrc;         // Fichier Source
    FILE *pFileDest;        // Fichier Destination

    char buffer[512];       //Buffer
    int etatLecture;        //Lors de la copie, l'état lecture renvera un chiffre != 0 pour indiquer la fin de la lecture du fichier source.

 // Récupérer les options
    while ((opt = getopt (argc, argv, options)) != -1)
    {
        switch(opt)
        {
            case '?':
                printf("ERREUR : Un des paramètres n'est pas reconnu. Utiliser cp -h pour obtenir de l'aide. \n");
                return 1;
                break;
            case 'h':
                help = 1;
                break;
            default:
                printf("ERREUR : Une erreur est survenu lors de la saisie des paramètres. \n");
                return 1;
                break;
        }
    }

    if (help == 1)
        // Si -h
    {
        printf("Pour utiliser la fonction cp taper : cp [-options] [chemin source] [chemin destination] \n");
        printf("Astuce : vous pouvez concaténer les options : -l -a = -la \n \n");
        printf("\t -h : Affiche l'aide. \n");
        return 0;
    }

    /* ******** Récupération du fichier source et du chemin de destination ***************/
    if (argc > 1)
    {
        int i;
        for (i = 1; i<argc; i++)
        {
            if(argv[i][0] != '-')
            {
                if(pathSrc != NULL)
                {
                    if (pathDest != NULL)
                    {
                        printf("ERREUR : Vous ne pouvez spécifier qu'une seule destination. Saisir cp -h pour obtenir de l'aide \n");
                        return 1;
                    }
                    else
                    {
                        pathDest = argv[i];
                    }
                }
                else
                {
                    pathSrc = argv[i];
                }
            }
        }
    }
    /* ******** Verification que la commande contient bien une source et une destination ***************/
    if (pathSrc == NULL)
    {
        printf("ERREUR : Veuillez spécifier le nom du chemin source. Saisir cp -h pour obtenir de l'aide. \n");
        return 1;
    }
    if (pathDest == NULL)
    {
        printf("ERREUR : Veuillez spécifier le nom du chemin de destination. Saisir cp -h pour obtenir de l'aide. \n");
        return 1;
    }


    /* ******** Coeur de la fonction ***************/

    // Récupération du type du fichier analysé
    struct stat sb; //buffer
    stat(pathSrc, &sb); //récup info sur le path source

    if (S_ISDIR(sb.st_mode)) // SI DOSSIER
    {
        if (mkdir(pathDest, sb.st_mode) != -1)
        {
            printf("Copie du répertoire \"%s\" \n", pathSrc);
        }
    }
    else // Si fichier
    {
        //Ouverture du fichier source
        if ((pFileSrc = fopen(pathSrc,"rb")) == NULL)
        {
            printf("ERREUR : Le fichier source que vous avez spécifié n'a plus être ouvert. Vérifier que vous avez les droits nécessaires, et que ce fichier existe. Saisir cp -h pour obtenir de l'aide \n");
            return 1;
        }

        //Ouverture du fichier de destination
        if ((pFileDest = fopen(pathDest,"wb")) == NULL)
        {
            fclose(pFileSrc);
            printf("ERREUR : Le fichier destination que vous avez spécifié n'a plus être ouvert ou créé. Vérifier que vous avez les droits nécessaires. Saisir cp -h pour obtenir de l'aide \n");
            return 1;
        }

        //Copie du fichier.
        while ((etatLecture = fread(buffer, 1, 512, pFileSrc)) != 0)
        {
            printf("%s", buffer);
            fwrite(buffer, 1, etatLecture, pFileDest);
        }

        //Fermeture Propre des fichiers.
        fclose(pFileDest);
        fclose(pFileSrc);

    }

    return 0;
}
int main(int argc, char * argv[])
{
    cp(argc, argv);


    return 0;
}
