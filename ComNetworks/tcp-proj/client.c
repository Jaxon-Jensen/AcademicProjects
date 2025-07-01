/* Aaron Zandt */
/* CSCI3550 - TCP Project Client */

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 10*1024*1024

char *file_buffer = NULL;
int socket_fd = 0, file_fd = 0;

/**
 * @param returned_val the return value in question
 * @param err_val the value that would indicate that an error has occurred (can typically be found in man page)
 * @param error_msg a printf-style format string literal that will be printed to stderr in the case of an error
 *   (all further args are format args)
 * @result If `force != 0` or `returned_val == err_val`, clean up all resources, print formatted `err_msg`, and exit with `EXIT_FAILURE` (no return). Nothing otherwise.
 */
bool error_check(ssize_t returned_val, ssize_t err_val, const char *error_msg, ...);
bool error_check(ssize_t returned_val, ssize_t err_val, const char *error_msg, ...) {
    if (returned_val != err_val) return false;

    if (error_msg != NULL) {
        va_list args;
        va_start(args, error_msg);
        vfprintf(stderr, error_msg, args);
        va_end(args);
    }

    /* Clean up resources before exit. */
    if (file_buffer != NULL) {
        free(file_buffer);
    }
    if (socket_fd > 0) {
        close(socket_fd);
    }
    if (file_fd > 0) {
        close(file_fd);
    }

    return true;
}

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
    bool err;
    va_list args;
    if (force) returned_val = err_val;

    va_start(args, error_msg);
    err = error_check(returned_val, err_val, error_msg, args);
    va_end(args);
    if (err) exit(EXIT_FAILURE);
}

void handle_sigint(int sig);
void handle_sigint(int sig) {
    early_exit_check(true, 0, 0, "\nclient: Client interrupted. Shutting down.\n");
}

int main(int argc, char **argv) {
    struct sockaddr_in server_socket = {AF_INET, 0, {0}};
    ssize_t bytes_read, bytes_sent;
    uint16_t port;
    int i, ret_val;

    signal(SIGINT, handle_sigint);

    /* Catching basic errors. */
    if (argc < 4)
        early_exit_check(true, 0, 0, "client: USAGE: client <server_IP> <server_Port> file1 file2 ...\n");

    port = (uint16_t)atoi(argv[2]);
    if (port <= 1023 && port >= 0)
        early_exit_check(true, 0, 0, "client: ERROR: Port number is privileged.\n");

    /* set socket params. */
    server_socket.sin_port = htons(port);
    ret_val = inet_aton(argv[1], &server_socket.sin_addr);
    early_exit_check(false, ret_val, 0, "client: ERROR: Setting the IP address.\n");

    /* loop through file args. */
    for (i = 3; i < argc; i++) {
        if (i > 3) puts("");
        /* Get socket fd and connect. */
        socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        printf("client: Connecting to %s:%s...\n", argv[1], argv[2]);
        ret_val = connect(socket_fd, (struct sockaddr *)&server_socket, sizeof(server_socket));
        if (error_check(ret_val, -1, "client: ERROR: connecting to %s:%s\n", argv[1], argv[2]))
            continue;
        printf("client: Success!\n");

        /* Send the file. */
        printf("client: Sending: \"%s\"...\n", argv[i]);

        file_fd = open(argv[i], O_RDONLY);
        if (error_check(file_fd, -1, "client: ERROR: Failed to open: %s\n", argv[i]))
            continue;

        file_buffer = malloc(BUFFER_SIZE);
        if (error_check((ssize_t)file_buffer, (ssize_t)NULL, "client: ERROR: Failed to allocate memory.\n"))
            continue;

        bytes_read = read(file_fd, file_buffer, BUFFER_SIZE);
        if (error_check(bytes_read, -1, "client: ERROR: Unable to read: %s\n", argv[i]))
            continue;

        /* read what the client is sending into file_buffer */
        bytes_sent = 0;
        do {
            ret_val = send(socket_fd, file_buffer, bytes_read, 0);
            if (error_check(ret_val, -1, "client: ERROR: While sending data.\n"))
                break;
            bytes_sent += ret_val;
        } while (bytes_sent < bytes_read);
        if (ret_val == -1)
            continue; /* loop exited on error/break, continue to next file. */

        /* Wrap up resources, next loop or exit. */
        file_fd = close(file_fd);
        socket_fd = close(socket_fd);
        free(file_buffer);
        printf("client: Done.\n");
    }

    printf("\nclient: File transfer(s) complete.\nclient: Goodbye!\n");
    exit(EXIT_SUCCESS);
}
