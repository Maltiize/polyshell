
#include <stdio.h>
#include <memory.h>
#include <unistd.h>
 
void fout(void)
{
    printf("j'aime le jambon\n la cocaine \n les morses\n");
}

void fin()
{
    printf("n'importe quoi\n");
    char result[240];
    int c =0;
    while (!feof(stdin)&& c<240)
       {
           
           result[c]=fgetc(stdin);
           c++;
       }
    /*fgets(result,240,stdin);
    strcat(result," et les putes\n");*/
    printf(result);
}



int main( int argc, char ** argv )

  {
    FILE * fichier =NULL;
    fichier=fopen("Kernel.c","r+");
    /*create the pipe */
   int pfd[2];
   if (pipe(pfd) == -1)
     {
       printf("pipe failed\n");
       return 1;
     }
 
   /* create the child */
   int pid;
   if ((pid = fork()) < 0)
     {
       printf("fork failed\n");
       return 2;
     }
 
   if (pid == 0)
     {
       /* child */
       sleep(2);
       close(pfd[1]); /* close the unused write side */
       dup2(pfd[0], 0); /* connect the read side with stdin */
       close(pfd[0]); /* close the read side */
       /* execute the process (wc command) */
       fin();
       return 3;
     }
   else
     {
       /* parent */
       close(pfd[0]); /* close the unused read side */
       dup2(pfd[1], 1); /* connect the write side with stdout */
       close(pfd[1]); /* close the write side */
       /* execute the process (ls command) */
       char results[800];
       while (!feof(fichier))
       {
           putchar(fgetc(fichier));
       }
       //while(fgets(results,800,fichier)!=NULL)
       //printf(results);
       
       return 4;
     }
   return 0;
  }