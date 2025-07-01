#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

#define BUF_SIZE (100*1024*1024)  
void SIGINT_handler( int sig );
void cleanup(void);
int fd_in;
int bytes_read;
char *inbuf = NULL;
int sockfd = -1;
unsigned short int port;


/* SIGINT handler for the client */
void SIGINT_handler( int sig ) {

   /* Issue an error */
   fprintf( stderr, "client: Client interrupted. Shutting down.\n" );

   /* Cleanup after yourself */
   cleanup();

   /* Exit for 'reals' */
   exit( EXIT_FAILURE );

} /* end SIGINT_handler() */

void cleanup() {
    /* Close the socket */
    if( sockfd > -1 ) {
        close( sockfd );
        sockfd = -1;         /* Mark it as unused */
    }

    /* Close the output file */
    if( fd_in >= 0 ) {
        close( fd_in );       /* Close the file */
        fd_in = -1;           
    }

    /* deallocate memory */
    if( inbuf != NULL ) {
        free( inbuf );       /* Release it */
        inbuf = NULL;        
    }
}

int main( int argc, char *argv[] ) {
    struct in_addr     ia;    /* For Internet address */
    struct sockaddr_in sa;    /* For socket address */
    char *outbuf = NULL;    /* For storing outgoing data using 'send()' */
    int bytes_sent; /* keeps bytes sent for send function */
    int file_cntr;

    if(argc < 4) {
        fprintf( stderr, "client: USAGE: client <server_IP> <server_Port> file1 file2 ...\n" );
        exit( EXIT_FAILURE );
    }
    
    ia.s_addr = inet_addr( argv[1] ); /* setting the internet address */

    /* setting port */
    port = (unsigned short int) atoi( argv[2] ); 

    sa.sin_family = AF_INET;          /* Use IPv4 addresses */
    sa.sin_addr   = ia;               /* Attach IP address structure */
    sa.sin_port   = htons( port );    /* Set port number in Network Byte Order */

    outbuf = (void *) malloc( BUF_SIZE ); /* allocating mem for outbuf */
    if( outbuf == NULL ) {
        fprintf( stderr, "ERROR: Failed to allocate memory for buffer.\n" );
        cleanup();
        exit( EXIT_FAILURE );
    }

    for(file_cntr = 3; file_cntr<argc; file_cntr++){
        fprintf( stdout, "client: Connecting to %s:%d\n", argv[1], port);
        /* Create a new TCP socket */
        sockfd = socket( AF_INET, SOCK_STREAM, 0 );
        /* Check that it succeeded */
        if( sockfd < 0 ) {
            fprintf( stderr, "ERROR: Unable to obtain a new socket.\n" );
            cleanup();
            exit( EXIT_FAILURE );
        }

        /* Attempt to connect with argv[1]:argv[2] */
        if( connect( sockfd, (struct sockaddr *) &sa, sizeof( sa ) ) != 0 ) {
            fprintf( stderr, "ERROR: Attempting to connect with the server.\n" );
            cleanup();
            exit( EXIT_FAILURE );
        }
        
        fprintf( stdout, "client: Success!\n");
        /* open file */
        fd_in = open( argv[file_cntr], O_RDONLY );
            if( fd_in < 0 ) {
                /* Issue an ERROR message */
                fprintf( stderr, "ERROR: Failed to open: %s\n\n", argv[file_cntr] );
                continue;
            }
        
        /* Attempt to read the file. If fail terminate, else contiue as normal */
        bytes_read = read( fd_in, outbuf, BUF_SIZE );
        if( bytes_read <= 0 ) {
            /* Issue a proper error. */
            fprintf( stderr, "ERROR: Unable to read file: %s\n", argv[file_cntr] );
            /* Cleanup. */
            cleanup();
            /* Terminate the program. */
            exit( EXIT_FAILURE );
        }

        fprintf( stdout, "client: Sending: \"%s\"\n", argv[file_cntr]);
        /* Send the data out a given socket */
        bytes_sent = send( sockfd, (const void *) outbuf, bytes_read, 0 ); 
        if ( bytes_sent != bytes_read ) {
            fprintf( stderr, "ERROR: send(): Failed to send all data.\n" );
            cleanup();
            exit( EXIT_FAILURE );
        }
        fprintf( stdout, "client: Done.\n\n");
        if( sockfd > -1 ) {
            close( sockfd );
            sockfd = -1;         /* Mark it as unused */
        }
        memset(outbuf,0,BUF_SIZE);
    }

    fprintf( stdout, "client: File transfer(s) complete.\nclient: Goodbye!\n");

    cleanup(); /* clean and close the program*/
    exit( EXIT_SUCCESS );
}