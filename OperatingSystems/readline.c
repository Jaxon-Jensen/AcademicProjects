/* 
 * Auth: ((Jaxon Jensen))
 * Date: ((2/24/2024)) (Due: ((2/25/2024)) )
 * Course: CSCI4500
 * Preproj#: 2 (Readline/Writeline)
 * Desc: Source code for 'readline()' function.
 */

#include <unistd.h>
#include <sys/types.h>
#include "rwtest.h"

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
