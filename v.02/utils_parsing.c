//              header

#include "philosopher.h"

int ft_atop(const char *str)
{
    int i;
    long rsl;

    i = -1;
    rsl = 0;
    /*
    while(str[i] && (str[i] >= 9 && str[i] <= 13))
        i++;
    while(str[i] == '-' || str[di] == '+')
    {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }
    */
    while(str[i])
    {
        rsl = (rsl * 10) + (str[i] - '0');
        i++;
    }
    return (rsl)
}

int numeric(char **av, int i, int ac)
{
    while(av[ac])
    {
        while(av[ac][i])
        {
            if (av[ac][i] < '0' || av[ac][i] > '9' || ft_strlen(av[ac] > 10))
            return (0);
            i++;
        }
        i = 0;
        ac++;
    }
    return (1);
}