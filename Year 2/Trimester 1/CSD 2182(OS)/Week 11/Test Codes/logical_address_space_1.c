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
    printf("\n\nInside Child process....\n");
    printf("=======================================\n");
    printf("address of global variable: [ %p ]\n", &grace[0]);    
	  printf("address of local variable: [ %p ]\n", &game[0]);    
	  printf("address of main() function: [ %p ]\n\n", main);
  }
  else
  {
    int status;
    wait(&status); /*parent wait for child to complete*/
    printf("Inside Parent process....\n");
    printf("=======================================\n");
    printf("address of global variable: [ %p ]\n", &grace[0]);    
	  printf("address of local variable: [ %p ]\n", &game[0]);    
	  printf("address of main() function: [ %p ]\n\n", main);
  }
  return 0;
}
