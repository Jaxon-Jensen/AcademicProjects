/*
 * Auth: Jaxon Jensen
 * Date: 10-6-2023  (Due: 10-8-2023)
 * Course: CSCI-3550 (Sec: 851)
 * Desc:  PREPROJECT-03, Printing the hostname.
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

/*Control the array size from one place*/
#define ARRAY_SIZE 80

int main( void )  {
    /*Array sufficiently big to store the 'hostname' string*/
	char hostname[ ARRAY_SIZE ];

    /*Try to get host name and store in char array hostname*/
    if(!gethostname(hostname, ARRAY_SIZE)){
        /*On success of gethostname print the name returned*/
        printf("Local hostname: %s\n", hostname);
    } else {
        /*On fail print the function that caused the error and terminate with failure*/
        printf("ERROR: gethostname()\n");
        exit(EXIT_FAILURE);
    }
    /*successful completion of program terminate with success*/
    exit(EXIT_SUCCESS);
}