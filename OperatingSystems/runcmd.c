/*
 * Auth: Jaxon Jensen
 * Date: 4-12-2024  (Due: 4-14-2024)
 * Course: CSCI-4500 (Sec: 002)
 * Desc:  PREPROJECT-06, Run command given.
 */
#include <sys/types.h>
#include <sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#define MAX_ARGS_PER_CMD 10   /* Your instructor will NEVER go beyond this */

extern char **environ;
int wstatus  = -1;    /* To store status code from CHILD */
int rstatus = -1;    /* To store the ACTUAL stutus from the CHILD */
int runcmd( const char *pathname, char * const argv[], char * const envp[], int *rstatus );


int runcmd( const char *pathname, char * const argv[], char * const envp[], int *rstatus ){
    pid_t pid;        /* Store the PID of the child */
    pid = fork();     /* Fork here */

    if( pid < 0 ) {
        /* If error */
        perror( "ERROR" );
        return -1;
    } else {
        /* If I'm the CHILD */
        if( pid == 0 ) {
            if(execve(pathname, argv, environ) == -1){
                perror("ERROR");
        }
        }
        
        /* Otherwise, if I'm the PARENT */  
        else {
            if( wait( &wstatus ) < 0 ) {
                /* If error */
                perror( "ERROR" );
                return -1;
            } else {
                *rstatus = WEXITSTATUS( wstatus );  /* Return via poiner */
            }
        }
    }
    return *rstatus;
}

int main( int argc, char *argv[] )  {
    char *args[MAX_ARGS_PER_CMD] = {NULL};  /* Array to construct argument list for execve() */
    char *pathname = NULL;                  /* To store command we want to run */
    pathname = argv[1];   /* Copy the pointer meant to be the command */
    args[0] = pathname;   /* Also make a copy for 'execve()' arguments */
    int i;
      
    if(argc < 2){
      printf("USAGE: runcmd [ args ...]\n");
      return(EXIT_FAILURE);
    }
    /* Construct a proper arguments array for 'execve()' */
    for( i = 1; i<argc; i++){
        args[i-1] = argv[i];
    }
    args[argc-1] = NULL;
    /* Also ensure NULL is the LAST value in 'args[]' */

    /* Call runcmd */
    if(runcmd(pathname, args, environ, &rstatus) == -1){
      return(EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
    
}