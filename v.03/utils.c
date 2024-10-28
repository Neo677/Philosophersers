// header

#include "philo.h"

void    error_exit(const char *error)
{
    printf(RED"🚨  %s  🚨\n"RST, error);
    exit(EXIT_FAILURE);
}

