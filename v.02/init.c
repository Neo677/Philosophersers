//              header

#include "philosopher.h"

void    init_mutex(t_parse_struct *philo)
{
    pthread_mutex_init(&philo->args.write_mutex, NULL);
    pthread_mutex_init(&philo->args.die, NULL);
    pthread_mutex_init(&philo->args.time_eat_mutex, NULL);
    pthread_mutex_init(&philo->args.finish_mutex, NULL);
}

int initialize(t_parse_struct *phil)
{
    int i;

    i = 0;
    phil->args.start_timer = actual_time(); // todo
    phil->args.flag_end = 0;
    phil->args.nb_phil_finish_eat = 0;
    

    init_mutex(phil);

    while(i < phil->args.total)
    {
        phil->philo[i].id = i + 1;
        phil->philo[i].mls_eat = phil->args.start_timer;
        phil->philo[i].nb_philo_eat = 0;
        phil->philo[i].finish = 0;
        phil->philo[i].right_fork = NULL;

        pthread_mutex_init(&phil->philo[i].left_fork, NULL);

        if (phil->args.total == 1)
            return (1);
        if (i == phil->args.total - 1)
            phil->philo[i].right_fork = &phil->philo[0].left_fork;
        else
            phil->philo[i].right_fork = &phil->philo[i + 1].left_fork;
        i++;
    }
    return (1);
}