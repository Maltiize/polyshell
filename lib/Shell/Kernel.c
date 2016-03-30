#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>



#define MAX_NAME_SZ 256
#define MAX_NB_FUNC 20
#define STDIN 0
#define STDOUT 1
#define STDERR 0



typedef struct Function Function;
typedef struct Commande Commande;
typedef int (*Func)(int, char **);




char** str_split(char* a_str, const char a_delim);
int lclFunction(char * cmd);
int getStructFunct(char ** cmd);
int getType(char * partCmd);
Commande * parseCmd(char ** tokens ,int * retnbcmd);
void prompt(char *currentDir, char *hostName);
void clear();
void initialize();

enum State{ NOCMDSTART,CMDSTART,NEEDCMDNEXT,NEEDNOTCMDNEXT,NEWTHREAD};

enum Type{UNDEFINED,CMD,COMPLEMENTCMD,REDIRECTIONLEFTERROR,REDIRECTIONLEFT,REDIRECTIONRIGHTERROR,REDIRECTIONRIGHT,DOUBLECMD,LOGIC};



struct Commande {
    char * name;
    char * option;
    char * redirectionin;
    char * redirectionout;
    char * redirectionerror;
    char * redirectionkeyboard ;
    Func pfunc;
    int thread ;
    char logic ;
    int nboption;
    struct Commande * nextCmd;

};

struct Function {
    char * name ;
    Func pfunc;
};

int bonjour(int argc,char ** argv){
    int i;
    //printf("lol\n");
    printf("bonjour");
    for(i=1;i<argc;i++)
        printf("%s",argv[i]);
    printf("\n");
    return 0 ;
    
}

int auRevoir(int argc,char ** argv){
    printf("au revoir papa \n");

    return 0 ;

}


int aDemain(int argc,char ** argv){
    printf("a demain papa \n");

    return 0 ;

}

Function listeFu[MAX_NB_FUNC];
int nbfunction = 3;


void initialize(){
    int nb =3;
    int i ;
    Func tab[MAX_NB_FUNC]={bonjour,auRevoir,aDemain};
    char * name[MAX_NAME_SZ];
    name[0]="bonjour";
    name[1]="auRevoir";
    name[2]="aDemain";
    
    for(i=0;i<nb;i++){
        //printf("test %s \n",name[i]);
        listeFu[i].name=name[i];
        listeFu[i].pfunc=tab[i];
    }
}


Function getFunc(char * cmd){
    int i ;
   for(i=0;i<nbfunction;i++){
        //printf("get func %s%s\n",listeFu[i].name,cmd);
        if(strcmp(listeFu[i].name,cmd)==0)
            return listeFu[i];
        
    }
   
    Function ret ;
    ret.name =NULL;
    ret.pfunc=NULL ;
    return ret ;
    
}

int lclFunction(char * cmd){
    return !(getFunc(cmd).name == NULL) ;

}


int  fileListeFun(Commande *  liCmd , int nbCmd){
    int i;
    Function token ;
    //printf("%s \n",liCmd[0].name);

    for (i=0;i<nbCmd;i++){
        //printf("%d \n",nbCmd);
        token = getFunc(liCmd[i].name);
        //printf("%d \n",nbCmd);

        if(token.name==NULL)
            return 1;
        liCmd[i].pfunc=token.pfunc;
    }
    //printf("%d \n",nbCmd);

    return 0 ;
    
}


int exect(Commande *cmd ){
    int file = -1;
    char * tmp  ;  
    int idxToDel = 0; 

   
    if(fork()==0){
        if(cmd[0].redirectionout!=NULL){
            if(cmd[0].redirectionout[0]!='$')
                file = open(cmd[0].redirectionout,O_RDWR|O_CREAT|O_APPEND , S_IRUSR |S_IWUSR) ;
                
            else{
                tmp=cmd[0].redirectionout;
                memmove(&tmp[idxToDel], &tmp[idxToDel + 1], strlen(tmp) - idxToDel);
                file = open(tmp,O_RDWR|O_CREAT|O_TRUNC , S_IRUSR |S_IWUSR) ;
            }
            dup2(file,STDOUT);

        }
        if(cmd[0].redirectionerror!=NULL){
            if(cmd[0].redirectionerror[0]!='$')
                file = open(cmd[0].redirectionerror,O_RDWR|O_CREAT|O_APPEND , S_IRUSR |S_IWUSR) ;
                
            else{
                tmp=cmd[0].redirectionerror;
                memmove(&tmp[idxToDel], &tmp[idxToDel + 1], strlen(tmp) - idxToDel);
                file = open(tmp,O_RDWR|O_CREAT|O_TRUNC , S_IRUSR |S_IWUSR) ;
            }
            dup2(file,STDERR);

        }

        char ** option=str_split(cmd[0].option,' ');
        (*cmd[0].pfunc)(cmd[0].nboption,option);      
        if(file!=-1)
            close(file);
        exit(0);

    }
    else
        wait(NULL); // permet d'attendre la mort du fils

    return 0;

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
    Commande * listCmd = malloc(sizeof(Commande)*MAX_NB_FUNC);
    int i ;
    int nbCmd=0;
    enum State st = CMDSTART;
    char * strTmp;
    strTmp=strdup("");
    //printf("ok\n");
    if (tokens)
    {
        if(lclFunction(*(tokens))==0){
            perror("ERROR CMD INCONNUE \n");
            return NULL;

        }

        listCmd[nbCmd].name = *(tokens);
        listCmd[nbCmd].option = strdup(*(tokens));
        listCmd[nbCmd].nboption=1;

        nbCmd++;
        

        for (i = 1; *(tokens + i); i++)
        {
           //printf("cmd is %s\n",*(tokens + i));

            switch (getType2(*(tokens + i))){

                case CMD:
                    if(st!=NEEDCMDNEXT){
                        perror("ERROR STRUCT DEUX NOM DE COMMANDE A LA SUITE");
                        return NULL ;
                    }
                    listCmd[nbCmd].name = *(tokens + i);
                    listCmd[nbCmd].option = strdup(*(tokens));
                    listCmd[nbCmd].nboption=1;

                    //printf("option %s \n",listCmd[nbCmd-1].option);

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
                    listCmd[nbCmd-1].nboption++;

                   // printf("option - %s \n",listCmd[nbCmd-1].option);
                    break;
                    
                    
                    
                case REDIRECTIONLEFT :

                    if(st!=CMDSTART ){
                        perror("ERROR REDIRECTION MAL PLACEE");
                        return NULL ;
                    }
                    if (strcmp(*(tokens + i),"<")==0) 
                        strTmp=strdup("$");
                    strcat(strTmp,*(tokens+i+1));
                    listCmd[nbCmd-1].redirectionin=strTmp;
                    st=NEEDNOTCMDNEXT;
                    strTmp=strdup("");

                    break;
                    
                case REDIRECTIONRIGHT :
                    if(st!=CMDSTART ){
                        perror("ERROR REDIRECTION MAL PLACEE");
                        return NULL ;
                    }
                    if (strcmp(*(tokens + i),">")==0) 
                        strTmp=strdup("$");
                    strcat(strTmp,*(tokens+i+1));
                    //printf("looool %s\n",strTmp);

                    listCmd[nbCmd-1].redirectionout=strTmp;
                    st=NEEDNOTCMDNEXT;
                    strTmp=strdup("");

                    break;
                
                
                case REDIRECTIONLEFTERROR :
                    if(st!=CMDSTART ){
                        perror("ERROR REDIRECTION MAL PLACEE");
                        return NULL ;
                    }
                     if (strcmp(*(tokens + i),"2>")==0) 
                        strTmp=strdup("$");
                    strcat(strTmp,*(tokens+i+1));
                   // printf("looool %s\n",strTmp);
                    
                    listCmd[nbCmd-1].redirectionerror=strTmp;
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
                    if(st==CMDSTART){
                        strcat(listCmd[nbCmd-1].option," ");
                        strcat(listCmd[nbCmd-1].option,*(tokens + i));
                        listCmd[nbCmd-1].nboption++;
                        
                    }
                   

                    //printf("option u %s \n",listCmd[nbCmd-1].option);

                    break;
                case LOGIC :
                    if(st!=CMDSTART){
                        perror("ERROR UNEXCEPTED LOGIC ASSIGNEMENT ");
                        return NULL ;
                    }
                if(strcmp(*(tokens + i),"&&")==0)
                    listCmd[nbCmd-1].logic='&';
                else
                    listCmd[nbCmd-1].logic='|';


                    break;
                
            }

            //if (getType(*(tokens + i))==0) printf("i'm in");

            //printf(listCmd[nbCmd].name);
            //printf("subCMD=[%s] type %d\n", *(tokens + i),getType2(*(tokens + i)));
        }
        //printf("ok \n");
    }



    free(tokens);
    *retnbcmd=nbCmd;
    return listCmd;
}


int main (int argc, char ** argv){
    
    
    char** tokens;
    char currentDir[100] ;
    char hostName[100] ;
    char *name = malloc (MAX_NAME_SZ*sizeof(char));
    int nbcmd ;
    Commande * cmd =NULL ;
    
    initialize();
    
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
        if(strcmp(name,"")==0)
            continue ;
        else{
            tokens= str_split(name, ' ');
            cmd=parseCmd(tokens,&nbcmd);
            
            //printf("looool %d\n",(int)strlen(cmd[0].redirectionout));
            if(fileListeFun(cmd,nbcmd)!=0)
                perror("CMD UNKNOWN IN THE MEMORY");
            else
                exect(cmd);
            
        }
        

    }
    /*
    FILE * fichier =NULL;
    fichier=fopen("testpipe","r+");
     while (!feof(fichier))
       {
           putchar(fgetc(fichier));
       }
    printf("Have a wonderful day\n");*/
    return 0;

}
void clear(){
    system("clear");
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