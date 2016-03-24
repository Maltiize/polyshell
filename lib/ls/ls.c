/*
Fonction LS
Projet C - MiniShell - Polytech Nantes 2016

Suggestion amélioration:
- Un meilleur rendu graphique.
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <dirent.h>
#include <time.h>
#include <fcntl.h>

//#include <memory.h>
#include <string.h>
//#include <limits.h>

// Structure des arguments.
struct options
{
    char nomShort; // pour les formes -h
    char * nomLong;       // pour les formes --help
};


// Fonction qui traduit st_mode par le type du fichier analysé.
char* mode2Type(struct stat sb)
{
    char * string;
    switch (sb.st_mode & S_IFMT) {
            case S_IFREG:
                string = "Fichier Régulier";
                break;
            case S_IFDIR:
                string = "Répertoire";
                break;
            case S_IFCHR:
                string = "Périphérique sans stockage";
                break;
            case S_IFBLK:
                string = "Périphérique de stockage";
                break;
            case S_IFLNK:
                string = "Lien symbolique";
                break;
            case S_IFIFO:
                string = "Tube";
                break;
            case S_IFSOCK:
                string = "Socket";
                break;
            default:
                string = "Non Reconnu";
         }

    return string;
}

// Fonction qui traduit st_mode par les droits sur le fichier.
char* mode2Droits(struct stat sb)
{
    char string[12];

    // Propriétaire
    if ((sb.st_mode & S_IRUSR) == S_IRUSR)
        string[0]='r';
    else
        string[0]='-';

    if ((sb.st_mode & S_IWUSR) == S_IWUSR)
        string[1]='w';
    else
        string[1]='-';

    if ((sb.st_mode & S_IXUSR) == S_IXUSR)
        string[2]='x';
    else
        string[2]='-';

    string[3]='-';

    // Groupe du Proprio
    if ((sb.st_mode & S_IRGRP) == S_IRGRP)
        string[4]='r';
    else
        string[4]='-';

    if ((sb.st_mode & S_IWGRP) == S_IWGRP)
        string[5]='w';
    else
        string[5]='-';

    if ((sb.st_mode & S_IXGRP) == S_IXGRP)
        string[6]='x';
    else
        string[6]='-';

    string[7]='-';

    // Visiteur
    if ((sb.st_mode & S_IROTH) == S_IROTH)
        string[8]='r';
    else
        string[8]='-';

    if ((sb.st_mode & S_IWOTH) == S_IWOTH)
        string[9]='w';
    else
        string[9]='-';

    if ((sb.st_mode & S_IXOTH) == S_IXOTH)
        string[10]='x';
    else
        string[10]='-';

    string[11]='\0';

    return string;
}

char * mois2String(int mois) {
	switch(mois) {
		case 0:
			return "janvier";
		case 1:
			return "février";
		case 2:
			return "mars";
		case 3:
			return "avril";
		case 4:
			return "mai";
		case 5:
			return "juin";
		case 6:
			return "juillet";
		case 7:
			return "août";
		case 8:
			return "septembre";
		case 9:
			return "octobre";
		case 10:
			return "novembre";
		case 11:
			return "décembre";
        default:
            return "?mois?";
	}
}

int ls(int argc, char *argv[])
{
    // Récup des structures & déclarations
	struct stat sb; //fichier
    struct tm *tm;  //format time

    // Mise par défaut à "./" si pas de spécifications de chemin.
	if (argv[1] == NULL)
		argv[1] = ".";

    printf("Vous visitez le répertoire suivant: %s \n", argv[1]);

    //Définition Directory
	DIR *dirp;
	struct dirent *dptr;

    // Test l'ouverture du chemin et ouverture si OK, erreur sinon.
	if ((dirp=opendir(argv[1])) == NULL)
	{
		printf("Erreur, impossible d'ouvrir le répertoire");
		return 1;
	}

    //Pour chaque entrée du répertoire...
	while(dptr=readdir(dirp))
	{
        lstat(dptr->d_name, &sb);
            // droits d'accés
            printf( "%s \t", mode2Droits(sb));

            // Nombre de liens
            printf("%ld ", (long) sb.st_nlink);

            // ID User
			printf("%ld ", (long) sb.st_uid);

            // ID Group
            printf("%ld ", (long) sb.st_gid);

            // Block Size
            printf("%ld \t", (long) sb.st_blksize);

            // Date dernière modif
            // NOTE : tm->tm_year renvoie l'heure à partir de l'an 1900. d'où +1900.
			tm = localtime(&sb.st_mtime);
			printf("%d %s %d %d:%d \n", tm->tm_mday, mois2String(tm->tm_mon), 1900+(tm->tm_year), tm->tm_hour, tm->tm_min);

            // Nom de fichier
            printf("%-20.19s", dptr->d_name);

            // Type de Fichier
            printf( "%-20.9s", mode2Type(sb));
	}
	return 0;
}

int main(int argc, char *argv[])
{
    ls(argc, argv);
}
