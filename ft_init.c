#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_PHILOSOPHERS 5

void		ft_philo_receive(t_philo philosopher[], pthread_mutex_t forks[])
{
	int i;

	i = 0;
	while (i < NUM_PHILOSOPHERS)
	{
		philosopher[i].id = i;
		philosopher[i].l_fork = &forks[i];
		philosopher[i].r_fork = &forks[(i + 1) % NUM_PHILOSOPHERS];
		i++;
	}
}


