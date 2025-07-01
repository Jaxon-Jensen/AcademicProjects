/*
 * Auth: Jaxon Jensen
 * Date: 3-31-2024  (Due: 3-31-2024)
 * Course: CSCI-4500 (Sec: 002)
 * Desc:  PREPROJECT-05, Batchline Parser.
 */

/*Imports*/

#include<stdio.h>
#include<stdlib.h> 
#include<unistd.h>
#include<string.h>
#include<sys/types.h>

/*Globals*/

#define MAX_CMDLINE_SIZE 256
#define MAX_JOBS_PER_LINE 10
#define MAX_SIMPLE_CMDS 10
#define MAX_ARGS_PER_CMD 10
#define MAX_SEQOPS 10

/*Prototypes*/

int split_into_jobs( char *cmdline, char *jobs[], size_t count );
int scan_seqops( int seqops[], char *jobstr, size_t count );
int extract_simple_cmds(char *jobstr, char *simple_cmds[], size_t count);
int extract_cmd_args(char *simple_cmd, char **cmd, char *cmdargs[], size_t count);
int extract_cmd_args( char *simple_cmd, char **cmd, char *cmdargs[], size_t count);
int readline( int fd, char *buf, int bufsz);

/*Functions*/

int split_into_jobs( char *cmdline, char *jobs[], size_t count ){
    // Initialize counter
    int num_jobs = 0;

    // Split cmdline into tokens using strtok
    char *token = strtok(cmdline, ";");
    while (token != NULL && num_jobs < count) {
        jobs[num_jobs++] = token;
        token = strtok(NULL, ";");
    }

    // Return the number of jobs encountered
    return num_jobs;
}


int scan_seqops( int seqops[], char *jobstr, size_t count ){
    // Initialize counter
    int num_ops = 0;

    // Loop through jobstr
    for (int i = 0; jobstr[i] != '\0' && num_ops < count; i++) {
        // Check sequence ops
        if (jobstr[i] == '&' && jobstr[i + 1] == '&') {
            seqops[num_ops++] = 1; // Store 1 for &
            i++; // Skip next char
        } else if (jobstr[i] == '|' && jobstr[i + 1] == '|') {
            seqops[num_ops++] = 2; // Store 2 for |
            i++; // Skip next char
        }
    }

    // Return counter
    return num_ops;
}


int extract_simple_cmds(char *jobstr, char *simple_cmds[], size_t count) {
    // Initialize counter
    int num_cmds = 0;

    // Tokenize using & and |
    char *token = strtok(jobstr, "&|");
    while (token != NULL && num_cmds < count) {
        simple_cmds[num_cmds++] = token;
        token = strtok(NULL, "&|"); // Get rid of second symbol
    }

    // Return counter
    return num_cmds;
}


int extract_cmd_args(char *simple_cmd, char **cmd, char *cmdargs[], size_t count) {
    // Initialize counter
    int num_tokens = 0;

    // Get command
    char *token = strtok(simple_cmd, " ");
    *cmd = token;
    num_tokens++;

    // Get arguments
    while ((token = strtok(NULL, " ")) != NULL && num_tokens < count) {
        cmdargs[num_tokens - 1] = token;
        num_tokens++;
    }

    // Return counter
    return num_tokens;
}


int readline( int fd, char *buf, int bufsz ) {
    int rval = 0;
    char c;
    int err;

    while ((err = read(fd, &c, 1)) > 0) {
        if (rval >= bufsz - 1) {
            return -1; /* Buffer would overrun */
        }

        if (c == '\n') {
            buf[rval++] = '\0';  /* Add null terminator and increment rval */
            break;  /* Stop reading at newline character */
        }

        buf[rval++] = c; /* Add c to buffer and increment rval */
    }

    if (err < 0) {
        return err;  /* Return error */
    }

    return rval;  /* Return the number of characters read */

}

void showPrompt(){
    // Show the prompt to the user.
    printf( ">> " );
    fflush(stdout);
}
/*Main*/

int main(void) {
    char cmdline[MAX_CMDLINE_SIZE];     // For storing the input string from the user.
    char* jobs[MAX_JOBS_PER_LINE];      // For storing 'job' substrings.
    int  seqops[MAX_SEQOPS];            // For storing sequence operator codes
                                        //  for the current job being processed.
    char* simple_cmds[MAX_SIMPLE_CMDS]; // For storing simple command strings.
    char* cmd;                          // For storing the 'command word'.
    char* cmdargs[MAX_ARGS_PER_CMD];    // For storing additional 'argument words'.

    while(1) {

    showPrompt();

    // Read a complete line and store in buffer 'cmdline'.
    int bytes_read = readline( 0, cmdline, MAX_CMDLINE_SIZE );
    // If we read anything (even an empty line).
    if( bytes_read > 0 ) {
        printf("readline(): Got: \"%s\" (rval = %d)\n",cmdline, bytes_read);
        // Split input commandline by 'jobs'.
        int total_jobs = split_into_jobs( cmdline, jobs, MAX_JOBS_PER_LINE );

        // For _each_ job...
        for( int i = 0; i < total_jobs; ++i ) {
            printf("Job #%d: \"%s\"\n", i, jobs[i]);

            // Scan for sequence operators.
            int seqops_cnt = scan_seqops( seqops, jobs[i], MAX_SIMPLE_CMDS );
            printf("    seqops[] = [ ");
            for(int j = 0; j < seqops_cnt; j++){
                printf("%d ", seqops[j]);
            }
            printf("]\n");

            // Split the job into simple commands...
            int total_simple_cmds = extract_simple_cmds( jobs[i], simple_cmds, MAX_SIMPLE_CMDS );

            // For _each_ simple comand...
            for( int j = 0; j < total_simple_cmds; ++j ) {
                printf("    Simple Command #%d = \"%s\"\n", j, simple_cmds[j]);
                //Extract the commands and the arguments.
                int total_tokens = extract_cmd_args( simple_cmds[j], &cmd, cmdargs, MAX_ARGS_PER_CMD );
                printf("        cmd = \"%s\"\n", cmd);
                for(int k = 1; k < total_tokens; k++){
                    printf("        arg[%d] = \"%s\"\n", k-1, cmdargs[k-1]);
                }
                printf("\n");
            } // end for( each simple command )
            printf("\n");
            fflush(stdout);
        } // end for( each job )

    } else {
        printf( "readline(): Returned with code = %d\n", bytes_read );
        return( EXIT_SUCCESS );
    } // end if-else()

    } // end while()

    return( EXIT_SUCCESS );
}