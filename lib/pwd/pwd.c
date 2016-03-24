#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Fonction PWD return 0 si ca marche et print le chemin sinon return 0 et écrit qu'il y a un probleme
int pwd(int argc, char *argv[])
{
    char buff[PATH_MAX + 1];    // On stock la taille du chemin max + 1
    char* path = getcwd( buff, PATH_MAX + 1 );

        if( path != NULL )  //Si le chemin existe alors on l'écrit et on return
        {
            printf("%s \n", path);
            return 0;
        }
        else
        {
            printf("Erreur le chemin n'existe pas\n");
            return 1;
        }
}

int main(int argc, char *argv[])
{
    pwd(argc, argv);
}
