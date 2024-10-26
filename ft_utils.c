//              header

#include "philosopher.h"

int numeric(char **av, int i, int j)
{
    while(av[j])
    {
        while(av[j][i])
        {
            if (av[j][i] < 0 || av[j][i] > 9 || ft_strlen(av[j] > 10))
                return (0);
            i++;
        }
        i = 0;
        j++;
    }
    return (1);
}

int parse_arg(int ac, char **av, t_philosopher *philo)
{
    if ((ac == 5 || ac == 6 )&& numeric(av, 0, 1))
    {
        philo->a.total = ft_atoi(av[1]);
        philo->a.die = ft_atoi(av[2]);
        philo->a.eat = ft_atoi(av[3]);
        philo->a.sleep = ft_atoi(av[4]);
        philo->a.m_eat = -1;
        if (ac == 6)
            philo->a.m_eat = ft_atoi(av[5]);
        if (philo->a.total <= 0 || philo->a.die <= 0 || philo->a.eat <= 0 || philo->a.sleep <= 0)
            return (0);
        return (1);
    }
    return (0);
}

void    init_mutex(t_philosopher *philo)
{
    pthread_mutex_init(&philo->a.write_mutex, NULL);
    pthread_mutex_init(&philo->a.dead, NULL);
    pthread_mutex_init(&philo->a.time_eat, NULL);
    pthread_mutex_init(&philo->a.finish, NULL);
}

int initalize(t_what_philo *philo)
{
    int i;

    i = 0;
    philo->a.start = actual_time();
    philo->a.stop = 0;
    philo->a.nb_philo_finish = 0;
    init_mutex(philo);
    while(i < philo->a.total)
    {
        philo->ph[i].id = i + 1;
        philo->ph[i].ms_eat = philo->a.start_t;
        philo->ph[i].nb_eat = 0;
        philo->ph[i].finish = 0;
        philo->ph[i].r_fork = NULL;
        pthread_mutex_init(&philo->ph[i].l_fork, NULL);
        if (philo->a.total == 1)
            return (1);
        if (i == philo->a.total - 1)
            philo->ph
    }
}