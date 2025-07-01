/*
 * Auth: Jaxon Jensen
 * Date: 11-5-2023  (Due: 11-5-2023)
 * Course: CSCI-3550 (Sec: 851)
 * Desc:  PREPROJECT-04, Reading and writing in C.
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#define BUF_SIZE  (100*1024*1024)
char *buf = NULL;
int bytes_read;
int fd_in;
int fd_out;
void SIGINT_handler( int sig );
void cleanup(void);

void cleanup() {
    /* Clear the buffer */
    if( buf != NULL ) {
        free( buf );       /* Release it */
        buf = NULL;        
    } 

    /* Close the input file */
    if( fd_in >= 0 ) {
        close( fd_in );       /* Close the file */
        fd_in = -1;           
    }

    /* Close the output file */
    if( fd_out >= 0 ) {
        close( fd_out );       /* Close the file */
        fd_out = -1;           
    }
}

void SIGINT_handler( int sig ) {
   /* Issue a message */
   fprintf( stderr, "Whoops!  Program interrupted!\n" );
   /* Cleanup */
   cleanup();
   /* Terminate the program HERE */
   exit( EXIT_FAILURE );
}

int main( int argc, char *argv[] ) {
    char fname[80]; /* Dynamic file name */
    int file_cntr;
    int bytes_read;
    int bytes_written;

    if(argc < 2){ /*check if no arguments have been passed. iff no arguments have been passed then print an error and reprompt to try again */
        printf("ERROR: Must supply one or more arguments.  Try again.\n"); 
        exit( EXIT_FAILURE );
    }
    /* Attempt to initialize the file buffer. If fail terminate, else contiue as normal */
    buf = (char *) malloc( BUF_SIZE );
    if ( buf == NULL ) {
        fprintf( stderr, "ERROR: Could not allocate memory.\n" );
        exit( EXIT_FAILURE );
    }

    /* Install 'signal handler' for catching [CTRL]+[C] */
    signal( SIGINT, SIGINT_handler );


    for(file_cntr = 1; file_cntr < argc; file_cntr++){
        /* Attempt to initialize the file. If fail terminate, else contiue as normal */
        fd_in = open( argv[file_cntr], O_RDONLY );
        if( fd_in < 0 ) {
            /* Issue an ERROR message the proper way. */
            fprintf( stderr, "ERROR: Failed to open: %s\n", argv[file_cntr] );
            /* Cleanup. */
            cleanup();
            /* Terminate properly. */
            exit( EXIT_FAILURE );
        }

        /* Attempt to read the file. If fail terminate, else contiue as normal */
        bytes_read = read( fd_in, buf, BUF_SIZE );
        if( bytes_read < 0 ) {
            /* Issue a proper error. */
            fprintf( stderr, "ERROR: Unable to read file: %s\n", argv[file_cntr] );
            /* Cleanup. */
            cleanup();
            /* Terminate the program. */
            exit( EXIT_FAILURE );
        }

        /* Close the input file */
        close(fd_in);

        /* Update file name */
        sprintf( fname, "file-%02d.dat", file_cntr );

        /* Attempt to open the output file. If fail terminate, else contiue as normal */
        fd_out = open( fname, O_CREAT|O_WRONLY|O_TRUNC,  S_IRUSR|S_IWUSR );
        if( fd_out < 0 ) {
            /* Issue a proper error. */
            fprintf( stderr, "ERROR: Could not create: %s\n", fname );
            /* Clean up. */
            cleanup();
            /* Exit. */
            exit( EXIT_FAILURE );
        }

        /* Attempt to write to the output file. If fail terminate, else contiue as normal */
        bytes_written = write( fd_out, buf, (size_t) bytes_read );
        if (bytes_written != bytes_read ) {
            /* Issue a proper error. */
            fprintf( stderr, "ERROR: Error writing ALL bytes.\n" );
            /* Clean up. */
            cleanup();
            /* Terminate. */
            exit( EXIT_FAILURE );
        }

        /* Close the output file */
        close(fd_out);
    }





    cleanup();
    exit( EXIT_SUCCESS ); /* ends the program*/
}
