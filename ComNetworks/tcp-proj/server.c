/* Aaron Zandt */
/* CSCI3550 - TCP Project Server */

/*

NOTE: I used the "strings" utility to extract the strings from test_server such that they could be re-used.

*/

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 10*1024*1024
#define SOCKET_FD 0
#define CLIENT_FD 1
#define OUTPUT_FD 2
#define FD_COUNT 3

/* {socket_fd, client_fd, output_fd}, index with FD constants above */
int fds[FD_COUNT] = {0};
/* main chunk of memory we'll be using to store the data between receiving and storing (should be of size BUFFER_SIZE) */
char *file_buffer = NULL;

/**
 * @param force guarantees an early exit if `true` aka `!= 0`
 * @param returned_val the return value in question
 * @param err_val the value that would indicate that an error has occurred (can typically be found in man page)
 * @param error_msg a printf-style format string literal that will be printed to stderr in the case of an error
 *   (all further args are format args)
 * @result If `force != 0` or `returned_val == err_val`, clean up all resources, print formatted `err_msg`, and exit with `EXIT_FAILURE` (no return). Nothing otherwise.
 */
void early_exit_check(bool force, ssize_t returned_val, ssize_t err_val, const char *error_msg, ...);
void early_exit_check(bool force, ssize_t returned_val, ssize_t err_val, const char *error_msg, ...) {
    int i;
    if (!force && returned_val != err_val) return;

    if (error_msg != NULL) {
        va_list args;
        va_start(args, error_msg);
        vfprintf(stderr, error_msg, args);
        va_end(args);
    }
    for (i = 0; i < FD_COUNT; i++)
        if (fds[i] > 0)
            close(fds[i]);
    if (file_buffer != NULL)
        free(file_buffer);

    exit(EXIT_FAILURE);
}

/**
 * handles SIGINT, allowing early termination through user input (usually ctrl+c)
 */
void handle_sigint(int sig);
void handle_sigint(int sig) {
    early_exit_check(true, 0, 0, "\nserver: Server interrupted. Shutting down.\n");
}

/**
 * \~%\~ entry point \~%\~
 */
int main(int argc, char **argv) {
    uint16_t port;
    int sock_reuse_flag = 1, file_count = 1, ret_val = 0;
    struct sockaddr_in client_sockaddr, socket_info = {AF_INET, 0, {0}};
    socklen_t client_sockaddr_size = sizeof(client_sockaddr);

    /* First and foremost, hook in the signal handler. */
    signal(SIGINT, handle_sigint);

    /* length check on arguments */
    if (argc != 2)
        early_exit_check(true, 0, 0, "server: USAGE: server <listen_Port>\n");

    /* port validity check (make sure we're in a good range) */
    port = (uint16_t)atoi(argv[1]);
    if (port <= 1023 && port >= 0)
        early_exit_check(true, 0, 0, "server: ERROR: Port number is privileged.\n");

    /* retrieve memory for the buffer we'll be reading to. */
    file_buffer = malloc(BUFFER_SIZE);
    early_exit_check(false, (ssize_t)file_buffer, 0, "server: ERROR: Failed to allocate memory.\n");

    /* set up the socket_info parameters (get things in proper byte order) */
    socket_info.sin_port = htons(port);
    ret_val = inet_aton("127.0.0.1", &socket_info.sin_addr);
    early_exit_check(false, ret_val, 0, "server: ERROR: Can't process \"127.0.0.1\" to network byte order. (running on wrong platform?)\n");

    /* retrieve socket file descriptor */
    fds[SOCKET_FD] = socket(AF_INET, SOCK_STREAM, 0);
    early_exit_check(false, fds[SOCKET_FD], -1, "server: ERROR: Failed to create socket.\n");

    /* prevent "already in use" when closing and opening the same socket */
    ret_val = setsockopt(fds[SOCKET_FD], SOL_SOCKET, SO_REUSEADDR, (const void *)&sock_reuse_flag, sizeof(int));
    early_exit_check(false, ret_val, -1, "server: ERROR: setsockopt() failed.\n");

    /* apply socket_info parameters to the socket fd */
    ret_val = bind(fds[SOCKET_FD], (struct sockaddr *)&socket_info, sizeof(socket_info));
    early_exit_check(false, ret_val, -1, "server: ERROR: Failed to bind socket.\n");

    /* mark the socket as a 'listener', now able to accept/receive data */
    ret_val = listen(fds[SOCKET_FD], 32);
    early_exit_check(false, ret_val, -1, "server: ERROR: listen(): Failed.\n");

    printf("server: Server running.\nserver: Awaiting TCP connections over port %d...\n", port);
    while (true) {
        size_t bytes_received;
        char output_filename[12] = {0};

        /* wait here until another socket comes in to send data, connection will be represented with client fd */
        fds[CLIENT_FD] = accept(fds[SOCKET_FD], (struct sockaddr *)&client_sockaddr, &client_sockaddr_size);
        early_exit_check(false, fds[CLIENT_FD], -1, "server: ERROR: While attempting to accept a connection.\n");
        printf("server: Connection accepted! (file desc = %d)\nserver: Receiving file...\n", fds[CLIENT_FD]);

        /* actually get the bytes that are being sent, store into file_buffer */
        do {
            bytes_received = recv(fds[CLIENT_FD], file_buffer, BUFFER_SIZE, MSG_WAITALL);
        } while (bytes_received > 0);
        early_exit_check(false, bytes_received, -1, "server: ERROR: Reading from socket.\n");

        snprintf(output_filename, 12, "file-%02d.dat", file_count);
        printf("server: Saving file: \"%s\"...\n", output_filename);

        /* create new file that the data will be stored into */
        fds[OUTPUT_FD] = open(output_filename, O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);
        early_exit_check(false, fds[OUTPUT_FD], -1, "server: ERROR: Unable to create: %s.\n", output_filename);

        /* write the data from file_buffer in memory into storage, i.e. the output fd */
        ret_val = write(fds[OUTPUT_FD], file_buffer, (size_t)bytes_received);
        early_exit_check(false, ret_val, -1, "server: ERROR: Unable to write: %s.\n", output_filename);
        
        /* done writing, close the output file */
        close(fds[OUTPUT_FD]);

        /* reset file_buffer */
        memset(file_buffer, 0, (size_t)bytes_received);

        /* close this connection, increment file count, end of this loop */
        printf("server: Finished.  Closing closed (file desc = %d).\n\n", fds[CLIENT_FD]);
        close(fds[CLIENT_FD]);
        file_count += 1;
    }
}
