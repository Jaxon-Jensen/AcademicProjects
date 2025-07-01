/*
 * Auth: Jaxon Jensen
 * Date: 3-3-2024  (Due: 3-3-2024)
 * Course: CSCI-4500 (Sec: 002)
 * Desc:  PREPROJECT-03, simple check access program.
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main( int argc, char *argv[] ) {
   int i;
    if(argc < 2){ /*check if no arguments have been passed. iff no arguments have been passed then print an error and show usage*/
        printf("ERROR: Usage: accesscheck <pathname>\n"); 
        exit( EXIT_FAILURE );
    } 
    printf("Checking: \"%s\"\n", argv[1]); /*iff arguments have been passed this prints the file name to be checked*/
    
    /* check if file exists and prints corresponding output*/
    i = access( argv[1], F_OK );
    if (i < 0){
        printf( "F_OK = -1\n\tERROR: %s (errno = %d)\n", strerror(errno), errno );
    } else {
        printf("F_OK = 0\n");
    }
    /* check if file is readable and prints corresponding output*/
    i = access( argv[1], R_OK );
    if (i < 0){
        printf( "R_OK = -1\n\tERROR: %s (errno = %d)\n", strerror(errno), errno );
    } else {
        printf("R_OK = 0\n");
    }
    /* check if file can be written to and prints corresponding output*/
    i = access( argv[1], W_OK );
    if (i < 0){
        printf( "W_OK = -1\n\tERROR: %s (errno = %d)\n", strerror(errno), errno );
    } else {
        printf("W_OK = 0\n");
    }
    /* check if file is executable and prints corresponding output*/
    i = access( argv[1], X_OK );
    if (i < 0){
        printf( "X_OK = -1\n\tERROR: %s (errno = %d)\n", strerror(errno), errno );
    } else {
        printf("X_OK = 0\n");
    }
    exit( EXIT_SUCCESS );
} /* end main() */