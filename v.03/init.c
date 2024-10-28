//          header

#include "philo.h"

static void ft_assign_fork(t_philospher *philo, t_fork *forks, int position)
{
     
}

static void philo_init(t_table *table)
{
    int i;
    t_philospher *philo;

    i = -1;
    while(++i < table->philo_nbr)
    {
        philo = table->philos + i;
        philo->id = i + 1;
        philo->full = false;
        philo->meals_cnt = 0;
        philo->table = table;

        ft_assign_fork(philo, table->fork, i);
    }
}

void data_init(t_table *table)
{
    int i;

    i = -1;

    table->end_simaltions = false;
    table->philos = safe_malloc(sizeof(t_philospher) * table->philo_nbr);
    table->fork = safe_malloc(sizeof(t_fork) * table->philo_nbr);

    while(++i < table->philo_nbr)
    {
        safe_mutex(table->fork[i].fork, INIT);
        table->fork[i].fork_id = i; // super pour debug
    }
    philo_init(table); // todo
}