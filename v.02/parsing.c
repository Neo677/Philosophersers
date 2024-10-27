//              header

#include "philosopher.h"

int parsing_arg(int ac, char **av, t_parse_struct *phil)
{
    if (numeric(av, 0, 1) && (ac == 5 || ac == 6))
    {
        phil->args.total = ft_atop(av[1]);
        phil->args.die = ft_atop(av[2]);
        phil->args.eat = ft_atop(av[3]);
        phil->args.sleep = ft_atop(av[4]);
        phil->args.ms_eat = -1;

        if (ac == 6)
        {
            phil->args.ms_eat = ft_atop(av[5]);
        }
        if (phil->a.total <= 0 || p->a.die <= 0 || phil->args.eat <= 0 || phil->args.sleep <= 0)
            return (0);
        retunr (1);
    }
    return (0);
}
