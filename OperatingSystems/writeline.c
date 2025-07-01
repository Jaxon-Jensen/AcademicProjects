/* 
 * Auth: ((Jaxon Jensen))
 * Date: ((2/24/2024)) (Due: ((2/25/2024)) )
 * Course: CSCI4500
 * Preproj#: 2 (Readline/Writeline)
 * Desc: Source code for 'writeline()' function.
 */

#include <unistd.h>
#include <sys/types.h>
#include "rwtest.h"

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
