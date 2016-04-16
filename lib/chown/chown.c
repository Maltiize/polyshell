#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <ctype.h> // isdigit ....

#include <getopt.h> // Pour les arguments
#include <pwd.h>  // Pour la fonction getpwnam qui change le nom;


// Pour le parsing de la commande
enum Etat
{
    Etat0Commande,
    Etat1Options,
    Etat2Droits,
    Etat3Paths
};


int myChown(int argc, char * argv[])
{
   // Déclaration variable pour arguments
    char opt; // Pour stocker les options passé en paramètre 1 à 1
    char * options = "h" ; // Les options disponibles

    int help = 0; // -h
    char * ordre = NULL; // Stock l'argument owner:group que l'on "splittera" par la suite.
    char * owner = NULL; // Stock le nouvelle utilisateur
    char * group = NULL; // Stock de nouveau groupe
    char * path = NULL; // Stock le chemin demandé


 // Récupérer les options
    while ((opt = getopt (argc, argv, options)) != -1)
    {
        switch(opt)
        {
            case '?':
                printf("ERREUR : Un des paramètres n'est pas reconnu. Utiliser chmod -h pour obtenir de l'aide. \n");
                return 1;
                break;
            case 'h':
                help = 1;
                break;
            /*default:
                printf("ERREUR : Une erreur est survenu lors de la saisie des paramètres. \n");
                return 1;
                break;*/
        }
    }
    if (help == 1) // Si -h
    {
        printf("Pour utiliser la fonction chown taper : chown [-options] [(Nom Du Nouveau Répertoire)] \n");
        printf("Astuce : vous pouvez concaténer les options : -l -a = -la \n \n");
        printf("\t -h : Affiche l'aide. \n");
        printf("\t \n");
        return 0;
    }

    // Récupérer le répertoire et le mode
    if (argc > 1)
    {
        int i;
        for (i = 1; i<argc; i++)
        {

             switch(i)
             {
                case 1:
                    ordre = argv[i];
                    break;
                case 2:
                    path = argv[i];
                    break;
             }

        }
    }


    if (path == NULL)
    {
        printf("ERREUR : Veuillez spécifier le nom d'un répertoire ou d'un fichier. Saisir chmod -h pour obtenir de l'aide. \n");
        return 1;
    }

    /* Coeur de la commande chown */

    // Récupération des uid et gid du fichier

    struct stat sb;
    stat(path, &sb);

    uid_t uid; // déclaration uid
    gid_t gid; // déclaration gid

    uid = sb.st_uid;    // récupération de l'actuelle uid
    gid = sb.st_gid;    // récupération de l'actuelle gid

    // Parsing de user & group
    int i = 0;

    if (ordre[0] != ':') // si n'est pas de type :user on récupère le owner
    {
        owner = malloc(255);
        while(ordre[i] != '\0' && ordre[i] != ':') //Récupération de l'owner jusqu'à la rencontre de : ou \0.
        {
            owner[i] = ordre[i];
            i++;
        }
        owner[i] = '\0';
    }

    if (ordre[i] == ':') //si on croise le séparateur : , on récupère le groupe
    {
        group =  malloc(255);
        int j = 0;
        i++;
        while(ordre[i] != '\0')
        {
            group[j] = ordre[i];
            i++; j++;
        }
        group[j] = '\0';
    }

        // Récupération de l'uId;
        struct passwd* own;

        if (owner != NULL)
        {
            uid = atoi(owner);
            if (!(own = getpwnam(owner)))
            {
                printf("ERREUR : Impossible d'obtenir l'uId du propriétaire : \"%s\" \n", owner);
                return 1;
            }
            uid = own->pw_uid;
        }

        // Récupération du gId;
        struct passwd* grp;

        if (group != NULL)
        {
            gid = atoi(group);
            if (!(grp = getpwnam(group)))
            {
                printf("ERREUR : Impossible d'obtenir le gId du groupe : \"%s\" \n", group);
                return 1;
            }
            gid = grp->pw_gid;
        }

        // Changement du fichier
        if (chown(path, uid, gid) != 0)
        {
            printf("ERREUR : Les modifications demandé sur le fichier n'ont pu être effectué.\n Assurez-vous d'avoir les droits nécéssaires. \n");
            return 1;
        }

    printf("Les propriétaires du fichier \"%s\" ont correctement été changés.\n", path);
    return 0;
}

int main(int argc, char * argv[])
{
    myChown(argc, argv);
    return 0;
}
