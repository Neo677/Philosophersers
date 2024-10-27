//      header

#include "philosopher.h"

int ft_exit(char *str)
{
    ft_putchar_fd("Error : ", 2);
    ft_putstr_fd(str, 2);
    return (0);
}

int check_death(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->a.dead);

    if (philo->a.stop)
    {
        pthread_mutex_unlock(&philo->a.dead);
        return (1); // return a error happened if the mutex isnt lock
    }
    pthread_mutex_unlock(&philo->a.dead);
    return (0);

}

int stop(t_philosopher *philo)
{
    int i;

    i = -1;
    while(!checker_death2(philo)) // todo
        ft_usleep(1); // todo
    while(i < philo->a.total)
    {
        pthread_join(philo->ph[i].id_thread, NULL);
        i++;
    }
    pthread_mutex_destroy(&philo->a.write_mutex);
    i = -1;
    while(i < philo->a.total)
    {
        pthread_mutex_destroy(&philo->ph[i].l_fork);
        i++;
    }
    if (philo->a.stop == 2)
        ft_printf("Each philosopher ate %d time(s)\n", philo->a.ms_eat)
    free(philo->ph);
}

