#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>




char** str_split(char* a_str, const char a_delim);
int lclFunction(char * cmd);
int getStructFunct(char ** cmd);
int getType(char * partCmd);
int parseCmd(char * cmd);

enum State{ NOCMDSTART,CMDSTART,NEEDCMDNEXT,NEEDNOTCMDNEXT,NEWTHREAD};

enum Type{ERROR,CMD,COMPLEMENTCMD,REDIRECTIONLEFT,REDIRECTIONRIGHT,DOUBLECMD,LOGIC};



struct Commande {
    char * name;
    char * option;
    char * redirectionin;
    char * redirectionout;
    char * redirectionerror;
    char * redirectionkeyboard ;
    struct Commande * nextCmd;

};

struct Function {
    char * name ;
    int (*pfunc)(int,char **);
}



Function listeFu[20];
int nbfunction = 0;


Function getFunc(char * cmd){
    int i =0 ;
    while(strcmp(listeFu[i].name,cmd) && i!=nbfunction )
        i++;
    if(strcmp(listeFu[i].name,cmd))
        return listeFu[i];
    return NULL ;
}

int lclFunction(char * cmd){
    if((strcmp(cmd,"grep") || strcmp(cmd,"ls") || strcmp(cmd,"ps") || strcmp(cmd,"find")))
        return 1;
    return 0;

}

void exect(Commande cmd ){
    Function f[10];
    int id =0;
    int file ;

    f = getFunc(f.name);


    while(f[id].nextCmd!=0){
        id++;
        f[id]=f[id-1].nextCmd
    }

    if(!fork()){
        if(f.redirectionout!=NULL){
            file = open(f.redirectionout,O_RDWR|O_CREAT|O_TRUNC , S_IRUSR |S_IWUSR) ;
            dup2(file,1);
        }
        if(f.redirectionerror!=NULL){
            file = open(f.redirectionerror,O_RDWR|O_CREAT|O_TRUNC , S_IRUSR |S_IWUSR) ;
            dup2(file,2);
        }

        

    }

}




/*
int getStructFunct(char ** cmd){
    int tmp ,i ;
    int count =0 ;
    enum State state ;

    if(lclFunction(cmd[0]))
        state =  NOCMDSTART;
    else{
        state = CMDSTART ;
        count ++ ;
    }

    for (i = 1; *(cmd + i); i++)
    {
        tmp = getType(*(cmd+i));
        if(tmp == 1){
            if(state==CMDSTART)
               state = NEEDCMDNEXT ;
            else
                return -1 ;
        }
        if(tmp == 2){
            if(state==NEEDNOTCMDNEXT || state == NEEDCMDNEXT)
                return -1 ;
            else
                state = NEEDNOTCMDNEXT ;
        }
        if(tmp == 0){
            if(state==NEEDNOTCMDNEXT)
                return -1 ;
            if(state==NEEDCMDNEXT){

            }

            }

        }

    }
    return count ;


}*/



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
        return REDIRECTIONRIGHT;
    else if(strcmp(partCmd,"<2")==0 )
        return REDIRECTIONLEFT;
    else if(strcmp(partCmd,"|")==0 )
        return DOUBLECMD;
    else if(partCmd[0]==opt)
        return COMPLEMENTCMD;

    else{
        if(lclFunction(partCmd))
            return CMD ;
        else
            return ERROR;
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


int parseCmd(char * cmd)
{
    int count =0 ;
    struct Commande listCmd[20];
    int nbCmd=0;
    while(*(cmd+count)){
        count++;
    }
    char * test = malloc(sizeof(char)*count*2);
    test = strdup(cmd);
    char** tokens;
    int i;


    tokens = str_split(test, ' ');
    if (tokens)
    {
        for (i = 0; *(tokens + i); i++)
        {
            switch (getType2(*(tokens + i))){

                case CMD:
                    listCmd[nbCmd].name = *(tokens + i);
                    nbCmd++;
                    break;
                case COMPLEMENTCMD:
                    strcat(listCmd[nbCmd-1].name," ");
                    strcat(listCmd[nbCmd-1].name,*(tokens + i));
                    printf("%s \n",listCmd[nbCmd-1].name);
                    break;
                case REDIRECTIONLEFT :
                    listCmd[nbCmd-1].redirectionin=*(tokens + i+1);
                    listCmd[nbCmd].redirectionout=listCmd[nbCmd-1].name;
                    break;
                case REDIRECTIONRIGHT :
                    listCmd[nbCmd-1].redirectionout=*(tokens + i+1);
                    printf("test %s\n",listCmd[nbCmd-1].redirectionout);
                    listCmd[nbCmd].redirectionin=listCmd[nbCmd-1].name;
                    break;
                case DOUBLECMD :
                    listCmd[nbCmd-1].nextCmd=*(tokens + i+1);
                    break;

            }

            //if (getType(*(tokens + i))==0) printf("i'm in");

            //printf(listCmd[nbCmd].name);
            printf("subCMD=[%s] type %d\n", *(tokens + i),getType(*(tokens + i)));
        }
        printf("\n");
    }


    for (i = 1; *(tokens + i); i++){

        printf("subCMD=[%s] type %d\n", *(tokens + i),getType(*(tokens + i)));



        free(*(tokens + i));


    }


    free(tokens);
    return 0;
}

int main (int argc, char ** argv){


    parseCmd("ls -tytghgh >> ps");
/*
    struct Commande c[2];
    c[0].name="castor";
    c[1].name="castor";
    struct Commande c2;
    c2.name="castoreee";
    struct Commande *c3;
    c3=&c2;
    c[0].nextCmd=c3;
    struct Commande *tmp=c[0].nextCmd;
    printf((*tmp).name);
    */
    return 0;

}
