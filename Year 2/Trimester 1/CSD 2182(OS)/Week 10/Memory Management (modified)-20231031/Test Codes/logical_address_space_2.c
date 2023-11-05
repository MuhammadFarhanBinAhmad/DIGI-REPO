#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // standard POSIX header file
#include <sys/wait.h> // POSIX header file for 'wait' function
int grace[1000];

int main()
{
  int res;
  char game[200];
    
  /* int fork(); */
  res=fork();
  
  if(res==0)
  {
    grace[0] = 4;
    game[0] = 'X';
    printf("\n\nInside Child process....\n");
    printf("=======================================\n");
    printf("address of global variable: [ %p ], its data: [ %d ]\n", &grace[0], grace[0]);
    printf("address of local variable: [ %p ], its data: [ %c ]\n", &game[0], game[0]);       
  }
  else
  {
    int status;
    wait(&status); /*parent wait for child to complete*/
    grace[0] = 5;
    game[0] = 'Y';
    printf("\n\nInside Parent process....\n");
    printf("=======================================\n");
    printf("address of global variable: [ %p ], its data: [ %d ]\n", &grace[0], grace[0]); 
    printf("address of local variable: [ %p ], its data: [ %c ]\n\n", &game[0], game[0]);
  }

   return 0;
}
