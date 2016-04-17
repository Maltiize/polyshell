#include "Kernel.h"
#include "Serv.h"




// variable globale stockant les différentes fonctions
Function listeFu[MAX_NB_FUNC];
int nbfunction = 10;
int returnVal;
char CurrentDir[MAX_NAME_SZ];
char DirLib[MAX_NAME_SZ];

GroupCommande DefaultGrp={NULL,NULL,'!'};
// Structure par defaut de Commande afin d'initialiser plus facilement les instances
Commande Default ={NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,'!',1,NULL};


// fonction traitant les groupes logiques à l'intérieur d'une commande 

GroupCommande * processingGroup(Commande * cmd,int nbCmd,int * retnb){
    int nbgroup =0 ;
    int i =0;
    Commande * tmp = &cmd[0] ;
    tmp = &cmd[0] ;
    
    // on compte le nombre de groupe logique
    while(tmp!=NULL){
        if(tmp->logic!='!'|| tmp->thread==1)
            nbgroup++;
        tmp = tmp->nextCmd;
    }
    
    // allocation memoire des groupes
    GroupCommande * ret = malloc(sizeof(GroupCommande)*nbgroup);
    for(i=0;i<nbgroup;i++)
        ret[i]=DefaultGrp;
    i=0;
    
    // on boucle sur les commandes 
    tmp =&cmd[0];
    while(tmp!=NULL && i<nbgroup){
       if(ret[i].cmd==NULL){
           
        // si il s'agit d'un nouveau groupe on recupere la premiere commande
        ret[i].cmd=tmp;
            if(i>0)
            
            // si ce n'est pas le premier groupe on le lie au precedent
                ret[i-1].nextgroup=&ret[i];
       }
         if(tmp->logic=='&' || tmp->logic=='|'){
             // si on rencontre un lien logique on passe sur un autre groupe
            ret[i].logic=tmp->logic;
            i++;
        }
        if(tmp->thread==1){
             // si on rencontre un nouveau thread on passe sur un autre groupe
            i++;
        }
        
        // on passeà la commade suivante 
        tmp = tmp->nextCmd;
    }
    i=0;
    
    // on supprime les liens inutiles entre les commandes 
    for(i=0;i<nbCmd;i++){
        if(cmd[i].logic=='&'|| cmd[i].logic=='|' || cmd[i].thread==1)
            cmd[i].nextCmd=NULL;
    }
    
    // on renvoit le nombre de groupe 
    (*retnb)=nbgroup;
    return ret;
    
}




// fonction de test
int bonjour(int argc,char ** argv){
    int i;
    printf("bonjour   ");
    char result[240];

    for(i=1;i<argc;i++)
        printf("%s",argv[i]);
    //printf("\n");
    
    //int c =0;
    fgets(result,240,stdin);
    printf("stdin %s\n",result);
    return 14 ;
    
}

int fout(int argc,char ** argv)
{
    printf("j'aime le jambon\n");
    return 0;
}

int fin(int argc,char ** argv)
{
    
    
    char result[240];
   
    fgets(result,240,stdin);
    strcat(result," et le poulet\n");
    printf("%s\n",result);
    return 0;
}
// fonction de test

int auRevoir(int argc,char ** argv){
    printf("au revoir papa \n");

    return 0;

}

// fonction de test

int aDemain(int argc,char ** argv){
    printf("a demain papa \n");

    return 0 ;

}

// version draft du init
void initialize(){
    getcwd(DirLib,MAX_NAME_SZ);
    getcwd(CurrentDir,MAX_NAME_SZ);
}

char * printdir(char *dir, char * file)
{
    DIR *dp;
    char * ret = malloc(sizeof(char)*1024);
    struct dirent *entry;
    struct stat statbuf;
    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return NULL;
    }
    chdir(dir);
    while((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode)) {
            /* Found a directory, but ignore . and .. */
            if(strcmp(".",entry->d_name) == 0 ||
                strcmp("..",entry->d_name) == 0)
                continue;
            //printf("%*s%s/\n",depth,"",entry->d_name);
            /* Recurse at a new indent level */
            ret=printdir(entry->d_name,file);
            if(ret!=NULL){
                chdir("..");
                closedir(dp);
                return ret;
            }
            
        }
        else {
            if(strcmp(file,entry->d_name) == 0){
                getcwd(ret,1024);
                strcat(ret,"/");
                //strcat(ret,file);
                return ret;
            }
        }
    }
    chdir("..");
    closedir(dp);
    return NULL;
}

// cherche une instance de Function à partir d'une chaine de caractères
// renvois NULL si rien n'est trouvé


int lclFunction(char * cmd){
    int vide;
    return !(getFunc(cmd,&vide) == NULL) ;

}

char * getFunc(char * cmd,int * System){
    int i ;
    char * path =NULL;
    char ** token ;
    char choice;
    path=printdir(DirLib,cmd);
    if(path!=NULL){
        *(System)=1;
        chdir(CurrentDir);
        return path;
    }
    path=printdir(CurrentDir,cmd);
    if(path!=NULL){
        *(System)=1;
        chdir(CurrentDir);
        return path;
    }
    else{
        printf("Fonction %s inconnue dans le local recherche dans PATH ? y/n\n", cmd);
        choice=getc(stdin);
        if(choice=='n')
            return NULL;
        path=getenv("PATH");
        token=str_split(path,':');
        for (i = 0; *(token + i); i++){
            path=printdir(*(token+i),cmd);
            if(path!=NULL){
                *(System)=0;
                chdir(CurrentDir);
                return path ;
            }
            
        }
        
    }
   
   
    return NULL ;
    
}

// remplie un tableau de structure Commande avec les pointeurs de fonctions 
// prorata le nom de function stockée dans les Commande 
int  fileListeFun(Commande *  liCmd , int nbCmd){
     //getcwd(CurrentDir,255);
    char * tmp = malloc(sizeof(char)*1024);
    int test =-1;
    int i;
    for (i=0;i<nbCmd;i++){
        tmp = getFunc(liCmd[i].name,&test);
        if(tmp==NULL)
            return 1;
        liCmd[i].path=tmp;
        liCmd[i].System=test;
    }
    return 0 ;
    
}

// execute une fonction en appliquant les différentes redirections
int exect(Commande cmd ){
    int val;
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
                
                
                //printf("%s\n",cmd.redirectionin);
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
        
        // on appelle la fonction
        if(cmd.System==0)
            val=system(cmd.option);
        else{
            char ** option=str_split(cmd.option,' ');
            strcat(cmd.path,cmd.name);
            execv(cmd.path,option); 
        }
            

        // on ferme le fichier si il a été ouvert
        if(file!=-1)
            close(file);
        if(val==0)
            exit(EXIT_SUCCESS);
        //printf("yesyesyes\n");
        exit(EXIT_FAILURE);
    }
    // on attend la fin du fils 
    else
        wait(&val);
    //printf("%d st devrais etre %d \n",val,EXIT_FAILURE);
   /*if(val==EXIT_FAILURE)
    printf("yesyesyes \n");*/
    return  val;

}

    

// Fonction particpant à l'analyse de l'automate
enum Type getType2(char * partCmd,int op){
    char opt='-' ;
    if( strcmp(partCmd,"&")==0)
        return NEWTHR;
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
        if(  op ==1 && lclFunction(partCmd)==1){
            return CMD ;}
        else
            return UNDEFINED;
    }


}


// fonction gérant le chainage de fonction 
int chainExec(Commande cmd){
    int pfd[2];
    pid_t pidt;
    int status=0;
    
    // si la commande est la dernière de la ligne on exit sur la valeur de renvois 
    if (cmd.nextCmd==NULL) {
        status=exect(cmd);
        if(status==0)
            exit(EXIT_SUCCESS);
        exit(EXIT_FAILURE);
        
    }
    // echec du pipe
   if (pipe(pfd) == -1)
     {
       printf("pipe failed\n");
       return 1;
     }
 
    /* creation du prossecus fils */
   int pid;
   if ((pid = fork()) < 0)
     {
       printf("fork failed\n");
       return 2;
     }
     
    // dans le cas d'une sous commande
   if (pid == 0)
     {  /*enfant*/
        close(pfd[0]); /* on ferme le coté lecture inutilisé */
        dup2(pfd[1], 1); /* on connect le coté ecriture avec stdout */
        close(pfd[1]); /* on ferme le coté écriture */
        exect(cmd);
        

        
        exit(10);     
       
     }
   else
     { /* parent */
        close(pfd[1]); /* on ferme le coté écriture inutilisé */
        dup2(pfd[0], 0);/* on connect le coté lecture avec stdin */
        close(pfd[0]); /* on ferme le lecture */
        if ((pidt = wait(&status)) == -1)
            /* on attent la fermeture du processus enfant*/                                 
           perror("wait error");
        else {

          
          
           /*on execute la commande */
           chainExec(cmd.nextCmd[0]);
           
           
           exit(status);
        }
         
     }
    
   return 0;
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
    int op =0;
    strTmp=strdup("");
    //printf("ok\n");
    for(i=0;i<MAX_NB_FUNC;i++)
        listCmd[i]=Default;
    if (tokens)
    {
        if(lclFunction(*(tokens))==0){
            
            perror("ERROR CMD INCONNUE\n");
            return NULL;

        }

        listCmd[nbCmd].name = *(tokens);
        listCmd[nbCmd].option = strdup(*(tokens));
        listCmd[nbCmd].nboption=1;
        nbCmd++;
        for (i = 1; *(tokens + i); i++)
        {
           //printf("cmd is %s\n",*(tokens + i));

            switch (getType2(*(tokens + i),op)){

                case CMD:

                    if(st!=NEEDCMDNEXT){
                        perror("ERROR STRUCT DEUX NOM DE COMMANDE A LA SUITE");
                        return NULL ;
                    }
                    listCmd[nbCmd].name = *(tokens + i);
                    listCmd[nbCmd].option = strdup(*(tokens));
                    listCmd[nbCmd].nboption=1;
                    nbCmd++;
                    op=0;
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
                    listCmd[nbCmd-1].logic='!';
                    op=0;
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
                st = NEEDCMDNEXT;
                listCmd[nbCmd-1].nextCmd=&listCmd[nbCmd];
                if(strcmp(*(tokens + i),"&&")==0)
                    listCmd[nbCmd-1].logic='&';
                else
                    listCmd[nbCmd-1].logic='|';


                    break;
                case NEWTHR :
                    if(st!=CMDSTART){
                        perror("ERROR UNEXCEPTED NEWTHREAD ASSIGNEMENT ");
                        return NULL ;
                    }
                st = NEEDCMDNEXT;
                listCmd[nbCmd-1].nextCmd=&listCmd[nbCmd];
                listCmd[nbCmd-1].thread=1;


                    break;
                
            }
        }
        //printf("ok \n");
    }
    listCmd[nbCmd-1].logic='L';


    free(tokens);
    *retnbcmd=nbCmd;
    return listCmd;
}
// fonction executant les groupes logiques ( && || ) de commandes 
int exectGroup (GroupCommande * ligrp){
    GroupCommande * tmp = &ligrp[0];
    int test;
    int state=0;
    while(tmp!=NULL){
        if(fork()==0){
                    chainExec((*tmp->cmd));
                }
                else{
                    wait(&test);
                    if(test==EXIT_SUCCESS)
                        state=0;
                    
                    else
                        state=1;
 
                }
        if(tmp->logic=='&' && state == 1)
            return 1 ;
        if(tmp->logic=='|' && state == 0)
            return 0;
        tmp=tmp->nextgroup;
    }
    return state ;
}



int main (int argc, char ** argv){
    
    int nbgroup;
    char** tokens;
    char currentDir[100] ;
    char hostName[100] ;
    char *name = malloc (MAX_NAME_SZ*sizeof(char));
    int nbcmd ;
    Commande * cmd =NULL ;
    //Commande * tmp =NULL;
    GroupCommande * group ;
    //GroupCommande * tmpgroup;
    //tmpgroup=NULL;
    initialize();
    int pidServ =-1 ;
    
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
        
        if(strcmp(name,"quit")==0){
             if(pidServ!=-1)
                kill(pidServ,SIGUSR1);
            break ;

        }
        else if(strcmp(name,"clear")==0)
            clear() ;
        else if(strcmp(name,"")==0)
            continue ;
        else if(strcmp(name,"launchServ")==0){
             if(pidServ==-1)
                pidServ=launchServ();
            else
                perror("SERVEUR ALREADY ACTIVE");
         }
        else if(strcmp(name,"quitServ")==0){
             if(pidServ!=-1){
                kill(pidServ,SIGUSR1);
                pidServ=-1;
             }
            else
                perror("SERVEUR ALREADY OFF");
         }
        
        else{
            tokens= str_split(name, ' ');
            if(strcmp(*(tokens),"cd")){
                chdir(*(tokens+1));
                getcwd(CurrentDir,MAX_NAME_SZ);
            }

            cmd=parseCmd(tokens,&nbcmd);
            if(cmd==NULL)
                continue ;
            if(fileListeFun(cmd,nbcmd)!=0)
                perror("CMD UNKNOWN IN THE MEMORY");
            else{
                group=processingGroup(cmd,nbcmd,&nbgroup);
                exectGroup(group);
                fflush(stdout);
            }
            
        }
        

    }

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