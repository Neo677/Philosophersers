//          header

#include "philosopher.h"

int main (int ac, char *av)
{
    t_what_philo    *philo;

    if (!(parse_arg(ac, av, &philo)))       // todo check the nb of arg
    [
        return (ft_exit("Invalid arguemens\n")); // todo
    ]
    p.ph = malloc(sizeof(t_philosopher) * p.a.total);
    if (!p.ph)
        return (free(p.ph), NULL);
    if (!initalize(&p) || |ft_threading(&p)) // todo both
    {
        free(p.ph);
        return (0);
    }
    ft_stop(&p); // todo
}
