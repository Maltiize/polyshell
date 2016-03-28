#include <stdio.h>
#include <stdlib.h>
#include <string.h> // pour strchr()

int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;
    if (fgets(chaine, longueur, stdin) != NULL)  // Si il n'y a pas d'erreur dans la saisie alors
    {
        positionEntree = strchr(chaine, '\n'); // On cherche avec strchr le \n
        if (positionEntree != NULL) // On échange le \n par un \0 afin d'enlever le retour à la ligne
        {
            *positionEntree = '\0';
        }
        return 1; // 1 :sans erreur
    }
    else
    {
        return 0; // 0 : E erreur
    }
}

// Fonction echo return 0 si ca marche et print le message sinon return 0 et écrit qu'il y a un probleme
int echo(int argc, char *argv[])
{
    char opt; // Pour stocker les options passé en paramètre 1 à 1
    char * options = "hnae" ; // Les options disponibles

    int help = 0; //option h
    int n = 0; // option n : Enleve le retour chariot (ENTRÉE)
    int a = 0; // option a : Laisse le retour chariot (ENTRÉE). En gros c'est le echo de base.
    int e = 0; //Prendre en compte le /n, le /t, et le /_ qui est une ligne de ___________ (délimitation de paragraphe

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
            case 'n':
                n = 1;
                break;
            case 'a':
                a = 1;
                break;
            case 'e':
                e = 1;
                break;
            default:
                printf("Une erreur est survenu lors de la saisie des paramètres. \n");
                return 1;
                break;
        }
    }

    if (help == 1)
    {
        printf("Pour utiliser la fonction echo taper : echo [-options] \n");
        printf("Echo : affiche le message écrit au clavier. \n");
        printf("\t -h : Affiche l'aide. \n");
        printf("\t -n : Permet de ne pas faire de retour chariot (ENTRÉE). \n");
        printf("\t -a : Permet de faire un retour chariot (ENTRÉE). \n");
        printf("\t -e : Permet d'accepter les '\\n', les '\\t' et les '\\_'. \n");
        printf("\t \t -'\\n' retour chariot\n");
        printf("\t \t -'\\t' tabulation\n");
        printf("\t \t -'\\_' Séparateur de paragraphes (ligne de _) \n");
        return 0;
    }

    char chaine[50];   //Peut etre essayer de rendre ca dynamique ? Utilisé un malloc ??

    if (n == 1)     //sans retour chariot
    {
        lire(chaine, 1000);
        printf("%s", chaine);
    }

    if (a == 1) //retour chariot
    {
    fgets(chaine, sizeof chaine, stdin);
    printf("%s", chaine);
    }

    if (e == 1) //caractère autoriser
    {
    fgets(chaine, sizeof chaine, stdin);
    int i=0;
    while(chaine[i] != '\0')    //tant qu'on est pas au bout de la chaine on fais des if pour changer les caractere
    {
        printf("%d",i);
        if(chaine[i]+chaine[i+1] == '\\t'){
            chaine[i]="     ";
        }
        else if(chaine[i]=='\\_'){
            chaine[i]="\n______________________________\n";
        }
        else if(chaine[i]=='\\n'){
        chaine[i]="\n";
        }
        i++;
    }

    printf("%s", chaine);
    }
}

int main(int argc, char *argv[])
{
    echo(argc, argv);
}