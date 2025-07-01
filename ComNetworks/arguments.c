/*
 * Auth: Jaxon Jensen
 * Date: 09-30-2023  (Due: 09-31-2023)
 * Course: CSCI-3550 (Sec: 851)
 * Desc:  PREPROJECT-02, Printing all command line args.
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main( int argc, char *argv[] ) {
    int i;
    if(argc < 2){ /*check if no arguments have been passed. iff no arguments have been passed then print an error and reprompt to try again*/
        printf("ERROR: Must supply one or more arguments.  Try again.\n"); 
        exit( EXIT_SUCCESS );
    }
    printf("Program Name: \"%s\"\n", argv[0]); /*iff arguments have been passed this prints the program name and number of arguments passed*/
    printf("Arguments: %i\n", argc-1); 

    for(i = 1; i < argc; i++){ /* uses the previously initialized i on line 10 to run a for loop that will iterate from i-(argc-1) each loop will print one of the passed arguments*/
        printf( "argv[%d]: \"%s\"\n", i, argv[i] ); 
    }
  exit( EXIT_SUCCESS ); /* ends the program*/
}