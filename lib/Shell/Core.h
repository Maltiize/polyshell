
#ifndef _MON_MODULE_H
#define _MON_MODULE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <netdb.h>
#include <netinet/in.h>

// le nombre de char max pour un nom de fonction
// le nombre max de fonction dans une commande 
#define MAX_NB_FUNC 20

// les flux standards

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define STARTING_PORT 1000 
#define NB_DEFAULT_CLIENT 25 
#define CODE_EMPTY  10
#define CODE_CLOSE  20
#define DEFAULT_LST 5
#define MAX_NAME_SZ 255


typedef struct Function Function;
typedef struct Commande Commande;
// permet de simplifier l'ecriture et l'appel des fonctions
typedef int (*Func)(int, char **);




struct Client {
    int etat ;
    int socket ;
    pid_t pid;
};



// structure à remplir pour l'execution d'une commande
struct Commande {
    char * name;
    char * option;
    char * redirectionin;
    char * redirectionout;
    char * redirectionerror;
    char * redirectionkeyboard ;
    Func pfunc;
    
    // thread indique un detachement du terminal
    int thread ;
    
    // logique indique un lien logique dans le chainage 
    char logic ;
    int nboption;
    
    // nextCmd est un pointeur vers la fonction suivante dans la commande 
    struct Commande * nextCmd;

};

struct Function {
    char * name ;
    Func pfunc;
};




char** str_split(char* a_str, const char a_delim);
int lclFunction(char * cmd);
int getStructFunct(char ** cmd);
int getType(char * partCmd);
Commande * parseCmd(char ** tokens ,int * retnbcmd);
void prompt(char *currentDir, char *hostName);
void clear();
void initialize();
int exect(Commande cmd );


#endif