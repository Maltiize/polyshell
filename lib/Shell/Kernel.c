#include "Core.h" 


// les etats de l'automates d'analyse de la commande
enum State{ NOCMDSTART,CMDSTART,NEEDCMDNEXT,NEEDNOTCMDNEXT,NEWTHREAD};

// les differents composantes d'une commande 
enum Type{UNDEFINED,CMD,COMPLEMENTCMD,REDIRECTIONLEFTERROR,REDIRECTIONLEFT,REDIRECTIONRIGHTERROR,REDIRECTIONRIGHT,DOUBLECMD,LOGIC};



// Structure par defaut de Commande afin d'initialiser plus facilement les instances
Commande Default ={NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,'y',1,NULL};



// fonction de test
int bonjour(int argc,char ** argv){
    int i;
    printf("bonjour   ");
    char result[240];

    for(i=1;i<argc;i++)
        printf("%s",argv[i]);
    printf("\n");
    
    //int c =0;
    fgets(result,240,stdin);
    printf("stdin %s\n",result);
    return 0 ;
    
}
// fonction de test

int auRevoir(int argc,char ** argv){
    printf("au revoir papa \n");

    return 0 ;

}

// fonction de test

int aDemain(int argc,char ** argv){
    printf("a demain papa \n");

    return 0 ;

}

// variable globale stockant les différentes fonctions
Function listeFu[MAX_NB_FUNC];
int nbfunction = 3;

// version draft du init
void initialize(){
    int nb =3;
    int i ;
    Func tab[MAX_NB_FUNC]={bonjour,auRevoir,aDemain};
    char * name[MAX_NAME_SZ];
    name[0]="bonjour";
    name[1]="auRevoir";
    name[2]="aDemain";
    
    for(i=0;i<nb;i++){
        listeFu[i].name=name[i];
        listeFu[i].pfunc=tab[i];
    }
}

// cherche une instance de Function à partir d'une chaine de caractères
// renvois NULL si rien n'est trouvé
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

// remplie un tableau de structure Commande avec les pointeurs de fonctions 
// prorata le nom de function stockée dans les Commande 
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

// execute une fonction en appliquant les différentes redirections
int exect(Commande cmd ){
    int file = -1;
    FILE * ff =NULL ;
    char * tmp  ;  
    int idxToDel = 0; 
    char name[MAX_NAME_SZ] ;

    if(fork()==0){
        
        // gestion du flux d'erreur
        // si un $ est contenu dans la premiere case il s'agit d'un simple 2> 2>> sinon
        if(cmd.redirectionerror!=NULL){
            if(cmd.redirectionerror[0]!='$')
                file = open(cmd.redirectionerror,O_RDWR|O_CREAT|O_APPEND , S_IRUSR |S_IWUSR) ;
            else{
                // si un $ se trouve dans la chaine il faut le supprimer
                tmp=cmd.redirectionerror;
                memmove(&tmp[idxToDel], &tmp[idxToDel + 1], strlen(tmp) - idxToDel);
                
                // on ouvre un fichier ayant pour nom la chaine contenue dans redirectionerror
                file = open(tmp,O_RDWR|O_CREAT|O_TRUNC , S_IRUSR |S_IWUSR) ;
            }
            // on redirige le flux 'erreur' vers le fichier ouvert
            dup2(file,STDERR);
    
        }
        
        // gestion du flux d'erreur
        // si un $ est contenu dans la premiere case il s'agit d'un simple < << sinon
        if(cmd.redirectionin!=NULL){
            
            if(cmd.redirectionin[0]!='$'){
                // si il s'agit d'un << il faut stocker tout ce qui est ecrit dans 
                // stdin jusqu'a que la chaine redirectionin soit tapée
                
                // on ouvre un fichier temporaire pour stocker ce que tape l'usr
                ff = tmpfile();
                while(1){
                        printf(">");
                        scanf("%s",name);
                        if(strcmp(name,cmd.redirectionin)==0)
                            break ;
                        strcat(name,"\n");
                        fputs (name,ff);
                    }
                // on retourne au debut du fichier 
                rewind(ff);
                file = fileno(ff);
                // necessaire car la premiere string est une ligne vide 
                fgets(name,MAX_NAME_SZ,stdin);
            }
                
            else{
                printf("%s\n",cmd.redirectionin);
                tmp=cmd.redirectionin;
                memmove(&tmp[idxToDel], &tmp[idxToDel + 1], strlen(tmp) - idxToDel);
                ff = fopen(tmp,"r");
                rewind(ff);
                file=fileno(ff);
            }
            dup2(file,STDIN);
         
        }
        // gestion du flux standards de sortie 
        // meme fonctionnement que pour stderr
        if(cmd.redirectionout!=NULL){
            if(cmd.redirectionout[0]!='$')
                file = open(cmd.redirectionout,O_RDWR|O_CREAT|O_APPEND , S_IRUSR |S_IWUSR) ;
                
            else{
                tmp=cmd.redirectionout;
                memmove(&tmp[idxToDel], &tmp[idxToDel + 1], strlen(tmp) - idxToDel);
                file = open(tmp,O_RDWR|O_CREAT|O_TRUNC , S_IRUSR |S_IWUSR) ;
            }
            dup2(file,STDOUT);
        }
        
        //on separe les options en sous chaines 
        char ** option=str_split(cmd.option,' ');
        
        // on appelle la fonction
        (*cmd.pfunc)(cmd.nboption,option);   
        
        // on ferme le fichier si il a été ouvert
        if(file!=-1)
            close(file);
        exit(0);
    }
    // on attend la fin du fils 
    else
        wait(NULL);
   
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
/*
int chainExec(Commande * cmd){
    
    int mypipe[2];
    FILE * ff ;
    int file ;
    //int stdoutCopy = dup(1);  
    char result [240];
    ff =tmpfile();
    file = fileno(ff);
// Clone stdout to a new descriptor

    //pid_t pid;
    if(fork()==0){
    dup2(file,1);
    printf("klmlkmlkmlkmlk\n");
    exit(0);
    }
    else{
    wait(NULL);
    rewind(ff);
    dup2(file,0);
    fgets(result,240,stdin);
    printf("%s",result);
    }

    close(file);


    return 0;
    
*/
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

void * rreturn(int ret){
    if(ret>0)
        exit(ret);
    return NULL ;
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
    for(i=0;i<MAX_NB_FUNC;i++)
        listCmd[i]=Default;
    if (tokens)
    {
        if(lclFunction(*(tokens))==0){
            perror("ERROR CMD INCONNUE \n");
            return NULL ;

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
                    if(st == NEEDNOTCMDNEXT)
                        st=CMDSTART;
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
        }
        //printf("ok \n");
    }
    free(tokens);
    *retnbcmd=nbCmd;
    return listCmd;
}


int mainKernel (int argc, char ** argv){
    
    
    char** tokens;
    char currentDir[100] ;
    char hostName[100] ;
    char *name = malloc (MAX_NAME_SZ*sizeof(char));
    int nbcmd ;
    Commande * cmd =NULL ;
    //int pid ;
    
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
                if(cmd==NULL)
                    continue ;
                //printf("looool %d\n",(int)strlen(cmd[0].redirectionout));
                if(fileListeFun(cmd,nbcmd)!=0)
                    perror("CMD UNKNOWN IN THE MEMORY");
                else{
                    exect(cmd[0]);
                    fflush(stdout);
                }
                
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
    free(name);
    return 0;

}
void clear(){
    system("clear");
}

void prompt(char *currentDir, char *hostName){

	getcwd(currentDir,sizeof(currentDir));
	gethostname(hostName, sizeof(hostName));

	
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