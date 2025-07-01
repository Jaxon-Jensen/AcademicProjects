/*
 * Auth: Jaxon Jensen
 * Date: 3-8-2024  (Due: 3-10-2024)
 * Course: CSCI-4500 (Sec: 002)
 * Desc:  PREPROJECT-03, Display all paths found.
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main( void )  {
    char *path = NULL;
    int i = 0;
	char *tok;          /* Stores the current token (i.e. substring) */
    char *delim = ":";  /* Specify delimiters used to guide 'strtok()' on how to
    break up the string */
    printf("Checking \"PATH\"...\n");
    /* Get the PATH */
    path = getenv( "PATH" );
    if( path != NULL ) {
        printf("PATH = \"%s\"\n", path);
        
        /* For each token (substring that is not NULL), execute the body portion...
        then keep retrieving the next token to re-enter another iteration
        over the _same_ string. */
        for( tok = strtok( path, delim ); tok != NULL;  tok = strtok( NULL, delim ) ) {
            printf("path[%d] = \"%s\"\n", i, tok);
            i++;
        }
    } else {
        printf("ERROR: getenv(): Unable to obtain 'PATH'.\n");
        exit( EXIT_FAILURE );
    }
    exit( EXIT_SUCCESS );
} /* end main() */