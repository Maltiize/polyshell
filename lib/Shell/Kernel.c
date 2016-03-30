#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX_NAME_SZ 256


typedef struct Function Function;
typedef struct Commande Commande;




char** str_split(char* a_str, const char a_delim);
int lclFunction(char * cmd);
int getStructFunct(char ** cmd);
int getType(char * partCmd);
Commande * parseCmd(char ** tokens ,int * retnbcmd);
void prompt(char *currentDir, char *hostName);
void clear();

enum State{ NOCMDSTART,CMDSTART,NEEDCMDNEXT,NEEDNOTCMDNEXT,NEWTHREAD};

enum Type{UNDEFINED,CMD,COMPLEMENTCMD,REDIRECTIONLEFTERROR,REDIRECTIONLEFT,REDIRECTIONRIGHTERROR,REDIRECTIONRIGHT,DOUBLECMD,LOGIC};



struct Commande {
    char * name;
    char * option;
    char * redirectionin;
    char * redirectionout;
    char * redirectionerror;
    char * redirectionkeyboard ;
    int (*pfunc)(int,char **);
    int thread ;
    struct Commande * nextCmd;

};

struct Function {
    char * name ;
    int (*pfunc)(int,char **);
};



Function listeFu[20];
int nbfunction = 0;


Function getFunc(char * cmd){
    int i =0 ;
    while(strcmp(listeFu[i].name,cmd) && i!=nbfunction )
        i++;
    if(strcmp(listeFu[i].name,cmd))
        return listeFu[i];
    Function ret ;
    ret.name =NULL;
    ret.pfunc=NULL ;
    return ret ;
    
}

int lclFunction(char * cmd){
    if((strcmp(cmd,"grep") ==0 || strcmp(cmd,"ls")==0 || strcmp(cmd,"ps")==0 || strcmp(cmd,"find")==0))
        return 1;
    return 0;

}
void fileListeFun(Commande *  liCmd , int nbCmd){
    
}

/*
void exect(Commande cmd ){
    Function f[10];
    int id =0;
    int file ;
    
    f[0] = getFunc(cmd.name);

    
    while(cmd.nextCmd!=0){
        id++;
        f[id]=f[id-1].nextCmd
    }
    
    if(!fork()){
        if(cmd.redirectionout!=NULL){
            file = open(cmd.redirectionout,O_RDWR|O_CREAT|O_TRUNC , S_IRUSR |S_IWUSR) ;
            dup2(file,1);
        }
        if(cmd.redirectionerror!=NULL){
            file = open(cmd.redirectionerror,O_RDWR|O_CREAT|O_TRUNC , S_IRUSR |S_IWUSR) ;
            dup2(file,2);
        }

        

    }

}
*/

int getType(char * partCmd){
    char opt='-' ;
    if(strcmp(partCmd,"&")==0 || strcmp(partCmd,"&&")==0 || strcmp(partCmd,"|")==0 || strcmp(partCmd,"||")==0 )
        return 1;
    else if(strcmp(partCmd,">")==0 || strcmp(partCmd,">>")==0 || strcmp(partCmd,"<<")==0 || strcmp(partCmd,"<")==0 )
        return 2;
    else if (partCmd[0]==opt)
        return -2 ;
    else{
        if(lclFunction(partCmd))
            return 0 ;
        else
            return -1;
    }


}
enum Type getType2(char * partCmd){
    char opt='-' ;
    if( strcmp(partCmd,"&")==0)
        return NEWTHREAD;
    else if( strcmp(partCmd,"&&")==0 || strcmp(partCmd,"||")==0 )
        return LOGIC;
    else if(strcmp(partCmd,">")==0 || strcmp(partCmd,">>")==0 )
        return REDIRECTIONRIGHT;
    else if(strcmp(partCmd,"<")==0 || strcmp(partCmd,"<<")==0 )
        return REDIRECTIONLEFT;
    else if(strcmp(partCmd,"2>")==0)
        return REDIRECTIONRIGHTERROR;
    else if(strcmp(partCmd,"<2")==0 )
        return REDIRECTIONLEFTERROR;
    else if(strcmp(partCmd,"|")==0 )
        return DOUBLECMD;
    else if(partCmd[0]==opt)
        return COMPLEMENTCMD;

    else{
        if(lclFunction(partCmd)==1)
            return CMD ;
        else
            return UNDEFINED;
    }


}


char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }



    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);
    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}
// & si besoin de créer un thread
// < << > >> si besoin de rediriger
// && || si besoin d'operateur logique
// = pour atribuer des valeur à une variable


Commande * parseCmd(char ** tokens ,int * retnbcmd)
{
    //int count =0 ;
    Commande listCmd[20];
    int i ;
    int nbCmd=0;
    enum State st = CMDSTART;
    printf("ok\n");
    if (tokens)
    {
        if(lclFunction(*(tokens))==0){
            perror("ERROR CMD INCONNUE \n");
            return NULL;

        }

        listCmd[nbCmd].name = *(tokens);
        nbCmd++;
        

        for (i = 1; *(tokens + i); i++)
        {
           printf("cmd is %s\n",*(tokens + i));

            switch (getType2(*(tokens + i))){

                case CMD:
                    if(st!=NEEDCMDNEXT){
                        perror("ERROR STRUCT DEUX NOM DE COMMANDE A LA SUITE");
                        return NULL ;
                    }
                    listCmd[nbCmd].name = *(tokens + i);
                    listCmd[nbCmd].option = *(tokens + i);
                    nbCmd++;
                    st=CMDSTART ;
                    
                    break;
                    
                case COMPLEMENTCMD:
                
                    if(st!=CMDSTART ){
                        perror("ERROR OPTION MAL PLACEE");
                        return NULL ;
                    }
                    strcat(listCmd[nbCmd-1].option," ");
                    strcat(listCmd[nbCmd-1].option,*(tokens + i));
                    printf("%s \n",listCmd[nbCmd-1].name);
                    break;
                    
                    
                    
                case REDIRECTIONLEFT :
                    if(st!=CMDSTART ){
                        perror("ERROR REDIRECTION MAL PLACEE");
                        return NULL ;
                    }
                    if (strcmp(*(tokens + i+1),"<")==0) listCmd[nbCmd-1].redirectionin=*(tokens + i+1);
                    else{
                        char * strTmp="$";
                        strcat(strTmp,*(tokens + i+1));
                        listCmd[nbCmd-1].redirectionin=strTmp;
                    }
                   
                    st=NEEDNOTCMDNEXT;
                    break;
                    
                case REDIRECTIONRIGHT :
                    if(st!=CMDSTART ){
                        perror("ERROR REDIRECTION MAL PLACEE");
                        return NULL ;
                    }
                    if (strcmp(*(tokens + i+1),">")==0) listCmd[nbCmd-1].redirectionout=*(tokens + i+1);
                    else{
                        char * strTmp="$";
                        strcat(strTmp,*(tokens + i+1));
                        listCmd[nbCmd-1].redirectionout=strTmp;
                    }
                    st=NEEDNOTCMDNEXT;
                    break;
                
                
                case REDIRECTIONLEFTERROR :
                    if(st!=CMDSTART ){
                        perror("ERROR REDIRECTION MAL PLACEE");
                        return NULL ;
                    }
                    
                    listCmd[nbCmd-1].redirectionerror=*(tokens + i+1);
                    st=NEEDNOTCMDNEXT;
                    break;
                    
                case REDIRECTIONRIGHTERROR:
                    if(st!=CMDSTART ){
                        perror("ERROR REDIRECTION MAL PLACEE");
                        return NULL ;
                    }
                    listCmd[nbCmd-1].redirectionerror=*(tokens + i+1);
                    st=NEEDNOTCMDNEXT;
                    break;
                    
                case DOUBLECMD :
                    if(st!=CMDSTART ){
                        perror("ERROR CHAINAGE MAL PLACEE");
                        return NULL ;
                    }
                    listCmd[nbCmd-1].nextCmd=&listCmd[nbCmd];
                    st=NEEDCMDNEXT;
                    break;
   
                    
                case UNDEFINED :
                 if(st!=CMDSTART && st!= NEEDNOTCMDNEXT){
                        perror("ERROR STRUCT CMD ");
                        return NULL ;
                    }
                
            }

            //if (getType(*(tokens + i))==0) printf("i'm in");

            //printf(listCmd[nbCmd].name);
            printf("subCMD=[%s] type %d\n", *(tokens + i),getType(*(tokens + i)));
        }
        printf("\n");
    }



    free(tokens);
    *retnbcmd=nbCmd;
    return listCmd;
}


int main (int argc, char ** argv){

    char** tokens;
    char currentDir[100] ;
    char hostName[100] ;
    char *name = malloc (MAX_NAME_SZ);
    int i ;
    int nbcmd ;
    Commande * cmd =NULL ;
    
     if (name == NULL) {
            printf ("No memory\n");
            return 1;
        }


	printf("Interpreteur de commande v1.0 \nTaper \"quit\" pour quitter\n");
    while(1){
        prompt(currentDir,hostName);
        /* Get the command, with size limit. */
        fgets (name, MAX_NAME_SZ, stdin);
        /* Remove trailing newline, if there. */
        if ((strlen(name)>0) && (name[strlen (name) - 1] == '\n'))
            name[strlen (name) - 1] = '\0';
        
        if(strcmp(name,"quit")==0)
            break ;
        if(strcmp(name,"clear")==0)
            clear() ;
        tokens= str_split(name, ' ');
        cmd=parseCmd(tokens,&nbcmd);
        
    }
    printf("Have a wonderful day\n");
    return 0;

}
void clear(){
  printf("\033c");
}

void prompt(char *currentDir, char *hostName){
	// username@nameofthemachine:currentdirectory

	getcwd(currentDir,sizeof(currentDir));
	gethostname(hostName, sizeof(hostName));

	// TEST : 
	//currentDir = get_current_dir_name();
	//getlogin_r(hostName, sizeof(hostName));
	// getenv("NAME");
	//getenv("PWD")
	//get_current_dir_name()


	// strcmp(currentDir,"") == *currentDir == NULL;
	
	if ((strcmp(currentDir,"") == 0) && (strcmp(hostName,"") == 0)){
		printf("%s@bash:~$ ", getlogin());

	}
	else if (strcmp(currentDir,"") == 0){
		printf("%s@%s:~$ ", getlogin(), hostName);

	}
	else if (strcmp(hostName,"") == 0){
		printf("%s@bash:%s$ ", getlogin(), currentDir);	
	}
	else {
		printf("%s@%s:%s$ ", getlogin(), hostName, currentDir);
	}
	fflush(stdout);
}