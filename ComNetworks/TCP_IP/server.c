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

#define BUF_SIZE (100*1024*1024)  /* Define a place for the size of the buffers */
void SIGINT_handler( int sig );
void cleanup(void);
int sockfd = -1;    /* Socket [file] descriptor */
int cl_sockfd;             /* Socket descriptor for accepted client */
int fd_out;
char *inbuf  = NULL;    /* For storing incoming data from 'recv()' */


/* SIGINT handler for the client */
void SIGINT_handler(int sig) {

   /* Issue an error */
   fprintf(stderr, "server: Server interrupted. Shutting down.\n");

   /* Cleanup after yourself */
   cleanup();

   /* Exit for 'reals' */
   exit(EXIT_FAILURE);

} /* end SIGINT_handler() */

void cleanup() {
    /* Close the socket */
    if( sockfd > -1 ) {
        close( sockfd );
        sockfd = -1;         /* Mark it as unused */
    }

    /* Close the client socket */
    if( cl_sockfd > -1 ) {
        close( cl_sockfd );
        cl_sockfd = -1;         /* Mark it as unused */
    }

    /* Close the output file */
    if( fd_out >= 0 ) {
        close( fd_out );       /* Close the file */
        fd_out = -1;           
    }

    if( inbuf != NULL ) {
        free( inbuf );       /* Release it */
        inbuf = NULL;        
    }
}

int main( int argc, char *argv[] ) {
    int val = 1;        /* Setting for one of the socket options */
    int bytes_read;    /* Keep track of *actual* vs *expected* bytes */
    char fname[80]; /* Dynamic file name */
    int file_cntr = 1;
    int bytes_written;
    unsigned short int port;
    struct in_addr ia; /* For Internet address */
    struct sockaddr_in sa;
    struct sockaddr_in cl_sa;
    socklen_t cl_sa_size = sizeof( cl_sa );

    /* getting and checking port number */
    if( argc < 2 ) {
        fprintf( stderr, "USAGE: server <listen_Port>\n" );
        cleanup();
        exit( EXIT_FAILURE );
    }

    port = (unsigned short int)atoi(argv[1]);
    if( port < 1024 ){
        fprintf( stderr, "ERROR: Privileged port.\n" );
        cleanup();
        exit( EXIT_FAILURE );
    }

    /* Prep the IP and set it to 127.0.0.1 */
    ia.s_addr = inet_addr("127.0.0.1");
    /* Fill the socket address structure fields */
    sa.sin_family = AF_INET;   /* Use IPv4 addresses */
    sa.sin_addr = ia;          /* Attach IP address structure */
    sa.sin_port = htons(port); /* Set port number in Network Byte Order */

    /* Allocating memory for buffer*/
    inbuf  = (void *) malloc( BUF_SIZE );
    if(inbuf == NULL ) {
        fprintf( stderr, "ERROR: Failed to allocate memory for buffer.\n" );
        cleanup();
        exit( EXIT_FAILURE );
    }

    /* Create a new TCP socket */
    sockfd = socket( AF_INET, SOCK_STREAM, 0 );
    /* Check that it succeeded */
    if( sockfd < 0 ) {
        fprintf( stderr, "ERROR: Unable to obtain a new socket.\n" );
        cleanup();
        exit( EXIT_FAILURE );
    }

    /* reuseable socket */
    if( setsockopt( sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *) &val, sizeof( int ) ) != 0 ) {
        fprintf( stderr, "ERROR: setsockopt() failed.\n" );
        cleanup();
        exit( EXIT_FAILURE );
    }


    /* Bind our listening socket to the socket address */
    if( bind( sockfd, (struct sockaddr *) &sa, sizeof( sa ) ) != 0 ) {
        fprintf( stderr, "ERROR: Socket binding failed.\n" );
        cleanup();
        exit( EXIT_FAILURE );
    }

    /* Turn an already-bound socket into a 'listening' socket
    to start accepting connection requests from clients. */
    if ( listen( sockfd, 32 ) != 0 ) {
        fprintf( stderr, "ERROR: COuld not turn socket into a 'listening' socket.\n" );
        cleanup();
        exit( EXIT_FAILURE );
    }


    /* Store the size of the socket address structure and 
    Clear all the bytes of this structure to zero */
    memset( (void *) &cl_sa, 0, sizeof( cl_sa ) );

    /* loop until close */
    while(1){
    
        /* waiting for connection */
        fprintf( stdout, "server: Awaiting TCP connections over port %d\n", port);
        cl_sockfd = accept( sockfd, (struct sockaddr *) &cl_sa, &cl_sa_size );

        /* Check we have a valid socket */
        if( cl_sockfd > 0 ) {
            fprintf( stdout, "server: Connection accepted!\n");

            /* Update file name */
            sprintf( fname, "file-%02d.dat", file_cntr );
            /* increment file counter */
            file_cntr++;
            /* Attempt to open the output file. If fail terminate, else contiue as normal */
            fd_out = open( fname, O_CREAT|O_WRONLY|O_TRUNC,  S_IRUSR|S_IWUSR );
            fprintf( stdout, "server: file created: %s\n", fname );
            if( fd_out < 0 ) {
                fprintf( stderr, "ERROR: Could not create: %s\n", fname );
                cleanup();
                exit( EXIT_FAILURE );
            }

            /* Attempt to read data from a socket */
            fprintf( stdout, "server: Receiving file...\n");
            bytes_read = recv( cl_sockfd, (void *) inbuf, BUF_SIZE, MSG_WAITALL );
            
            /* Check what was read */
            if( bytes_read >= 0 ) {

                fprintf( stdout, "server: Received file.\n");

                /* Attempt to write to the output file. If fail terminate, else contiue as normal */
                bytes_written = write( fd_out, inbuf, (size_t) bytes_read );
                if (bytes_written != bytes_read ) {
                    fprintf( stderr, "ERROR: Error writing ALL bytes.\n" );
                    cleanup();
                    exit( EXIT_FAILURE );
                }
                fprintf( stdout, "server: File saved to :%s\n", fname);

                /* Close the output file */
                if( fd_out >= 0 ) {
                    close( fd_out );       /* Close the file */
                    fd_out = -1;           
                }
                
                
                memset(inbuf,0,BUF_SIZE);

            } else if ( bytes_read == 0 ) {
                /* Close the client socket */
                if( cl_sockfd > -1 ) {
                    close( cl_sockfd );
                    cl_sockfd = -1;         /* Mark it as unused */
                }
                continue;
            } else {
                fprintf( stderr, "ERROR: An error ocurred while reading from socket: %d\n", sockfd );
                cleanup();
                exit( EXIT_FAILURE );
            }

        } else {
            fprintf( stderr, "ERROR: accept(): Connection request failed.\n" );
            cleanup();
            exit( EXIT_FAILURE );
        }

        /* closing the socket */
        if( cl_sockfd > -1 ) {
            close( cl_sockfd );
            cl_sockfd = -1;         /* Mark it as unused */
        }
        fprintf( stdout, "server: Connection closed.\n");
        fprintf( stdout, "server: Done.\n\n\n");
    }


}