/*
 * Auth:  Jaxon Jensen
 * Date:  05-03-2024  (Due: 05-05-2024)
 * Course: CSCI-4500 (Sec: 002)
 * Project#: 1 Simple Shell
 * Desc:  A program that runs a simplified shell
 */

/* Happy little libraries */
#include <stdio.h>    
#include <stdlib.h>    
#include <unistd.h>   
#include <string.h>   
#include <sys/types.h> 
#include <sys/wait.h>  

/* Happy little globals */
#define ARRAY_SIZE 1024 
#define MAX_CMDLINE_SIZE 256
#define MAX_JOBS_PER_LINE 10
#define MAX_SIMPLE_CMDS 10
#define MAX_ARGS_PER_CMD 10
#define MAX_SEQOPS MAX_SIMPLE_CMDS
#define MAX_TOKENS 10
#define MAX_PATHS 20
#define MAX_STRBUF_SIZE 80 
#define MAX_ARGS_PER_CMD 10 

/* Happy little globals of a different kind */
int bytes_read;
extern char **environ;
char *cmd;
char strbuf[MAX_STRBUF_SIZE];
char cmdline[MAX_CMDLINE_SIZE];
char *jobs[MAX_JOBS_PER_LINE];
char *simple_cmds[MAX_SIMPLE_CMDS];
char *cmdargs[MAX_ARGS_PER_CMD];
int wstatus = -1;
int rstatus = -1;
int seqops[MAX_SEQOPS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
char *args[MAX_ARGS_PER_CMD] = {NULL};
char *pathname = NULL;


/* Happy little function declarations */
void show_prompt(char *prompt);
int split_into_jobs(char *cmdline, char *jobs[], size_t count);
int scan_seqops(int seqops[], char *jobstr, size_t count);
int extract_simple_cmds(char *jobstr, char *simple_cmds[], size_t count);
int extract_cmd_args(char *simple_cmd, char **cmd, char *cmdargs[], size_t count);
int readline(int fd, char *buf, int bufsz);
int writeline(int fd, const char *str);
int runcmd(const char *pathname, char *const argv[], char *const envp[], int *rstatus);

void show_prompt(char *prompt) {
    /* Print given prompt and flush */
    printf("%s", prompt);
    fflush(stdout);
}

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

} /* end readline() */

int writeline( int fd, const char *str ) {
    char c;
    int rval = 0;
    int err = 1;

    while(1){
        /* Grab ONE character */
        c = str[rval++];

        /* If it's not the end of the string, send it! If write fails return error*/
        if( c != '\0' ) {
            err = write( fd, (const void *) &c, 1 ); 
            if (err != 1){
                return err;
            }
        } else {
            err = write( fd, (const void *) "\n", 1 );
            if (err != 1){
                return err;
            }
            break;
        }
    }
    return rval; /* return number of written chars */

} /* end writeline() */

int runcmd(const char *pathname, char *const argv[], char *const envp[], int *rstatus) {
    pid_t pid;    /* Store the PID of the child */
    pid = fork(); /* Fork here */

    if (pid < 0) {
        /* If error */
        perror("ERROR");
        return -1;
    } else {
        /* If I'm the CHILD */
        if (pid == 0) {
            if (execve(pathname, argv, envp)) {
                perror("ERROR: 'execve()'");
                return -1;
            }
        }
        /* Otherwise, if I'm the PARENT */
        else {
            if (wait(&wstatus) < 0) {
                /* If error */
                perror("ERROR");
                return -1;
            } else {
                *rstatus = WEXITSTATUS(wstatus); /* Return via poiner */
            }
        }
    }
    return *rstatus;
}

/* Happy little main */
int main(void) {
    /* Happy little variables nicely organized */
    int totalJobs, total_simple_cmds, totalCmdArgs, runResult, i, j;
    char *tok;
    char cmdPath[ARRAY_SIZE];
    char allPaths[MAX_PATHS][MAX_CMDLINE_SIZE];
    char token[ARRAY_SIZE];
    int numPaths = 0;
    int k = 0;
    int checkValue = 0;
    int validCmd = -1;
    char *path = NULL;
    char *delim = ":";

    /* Happy little environment path process */
    path = getenv("PATH");
    if (path != NULL) {
        strncpy(token, path, ARRAY_SIZE); /* fixing my mistake from the assignment */

        /* For each token (substring that is not NULL), execute the body portion...
        then keep retrieving the next token to re-enter another iteration
         over the _same_ string. */
        for (tok = strtok(token, delim); tok != NULL; tok = strtok(NULL, delim)) {
            strncpy(allPaths[numPaths], tok, MAX_CMDLINE_SIZE);
            /* ... do somthing with 'tok', which contains a substring... */
            numPaths++;
        } 
    } else {
        sprintf(strbuf,"ERROR: getenv(): Unable to obtain 'PATH'.\n");
        exit(EXIT_FAILURE);
    }

    /* Forever loop */
    while (1) {
        checkValue = 0;

        show_prompt(">>"); /* prompt */

        /* User input */
        bytes_read = readline(0, cmdline, MAX_CMDLINE_SIZE);

        /* Do stuff if we get stuff */
        if (bytes_read > 0) {
            /* ensure we got stuff not just white space */
            for (i = 0; cmdline[i] != '\0'; i++) {
                if (cmdline[i] != ' ' && cmdline[i] != '\t') {
                    checkValue = 1;
                    break;
                }
            } 
            if (checkValue != 1) {
                continue;
            }

            /* split into jobs */
            totalJobs = split_into_jobs(cmdline, jobs, MAX_JOBS_PER_LINE);

            /* for each job */
            for (i = 0; i < totalJobs; ++i) {
                /* get seqops */
                scan_seqops(seqops, jobs[i], bytes_read);

                /* split into simple cmds */
                total_simple_cmds = extract_simple_cmds(jobs[i], simple_cmds, MAX_SIMPLE_CMDS);

                /* for each simple cmd */
                for (j = 0; j < total_simple_cmds; ++j) {
                    /* get cmd args */
                    totalCmdArgs = extract_cmd_args(simple_cmds[j], &cmd, cmdargs, MAX_ARGS_PER_CMD);

                    /* If '/' then assume file path is provided otherwise go searching */
                    if (strchr(cmd, '/') == NULL) {
                        for (k = 0; k < numPaths; k++) {
                            sprintf(cmdPath, "%s/%s", allPaths[k], cmd);
                            /* Check if it exists and we can 'run' it... */
                            if (access(cmdPath, X_OK) == 0) {
                                validCmd = 0;
                                break;
                            } else {
                                validCmd = -1;
                            }
                        }
                    } else {
                        validCmd = 0;
                        sprintf(cmdPath, "%s", cmd);
                    }

                    if(validCmd == -1){
                        /* Print error */
                        sprintf( strbuf, "ERROR: file or command not found!");

                        /* Write it out when needed */
                        writeline( 1, strbuf );

                        /* seqops check */
                        if(seqops[j] == 1){
                            if (seqops[j+1] != 0){
                                while (seqops[j+1] == 1){
                                    j += 1;
                                } 
                                j += 1;
                                continue;
                            } else {
                                break;
                            }
                        } else if (seqops[j] == 2) {
                            continue;
                        }
                    }
                    /* Copy correct path to pathname and args[0] */
                    pathname = cmdPath;
                    args[0] = pathname;

                    /* Construct arguments for execve with null at end */
                    for (k = 1; k < totalCmdArgs; k++) {
                        args[k] = cmdargs[k - 1];
                    }
                    args[k] = NULL;

                    /* Call runcmd and check its return */
                    runResult = runcmd(pathname, args, environ, &rstatus);

                    /* Evaluate OR and AND seqops to see if we continue */
                    if(seqops[j] == 1){
                        if(runResult == 0){
                            continue;
                        } else if (seqops[j+1] != 0){
                            while (seqops[j+1] == 1){
                                j += 1;
                            } 
                            j += 1;
                            continue;
                        } else {
                            break;
                        }
                    } else if (seqops[j] == 2) {
                        if(runResult == 1){
                            continue;
                        } else if (seqops[j+1] != 0){
                            while (seqops[j+1] == 2){
                                j += 1;
                            } 
                            j += 1;
                            continue;
                        } else {
                            break;
                        }
                    }
                } 
            }
        }
        /* check EOF */
        else if (bytes_read == 0) {
            break;
        }
    }
    exit(EXIT_SUCCESS);
}