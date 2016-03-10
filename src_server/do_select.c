
#include <stdlib.h>
#include "bircd.h"

void	do_select(t_env *e)
{
	e->r = select(e->max + 1, &e->fd_read, &e->fd_write, NULL, NULL);
}

/*main(void)
{
    fd_set rfds;
    int retval;

    //Surveiller stdin (fd 0) en attente d'entrées 
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

    retval = select(1, &rfds, NULL, NULL, NULL);

    if (retval == -1)
        perror("select()");
    else if (retval)
        printf("Des données sont disponibles maintenant\n");
        // FD_ISSET(0, &rfds) est vrai 
    else
        printf("Aucune données durant les 5 secondes\n");

    exit(EXIT_SUCCESS);
}*/