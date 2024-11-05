/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:07:12 by thobenel          #+#    #+#             */
/*   Updated: 2024/10/30 14:07:15 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void assign_forks(t_philospher *philosopher, t_fork *forks, int philo_nbr) 
{
    if (philosopher->id % 2 == 0) 
	{
        philosopher->first_fork = &forks[philosopher->id];
        philosopher->second_fork = &forks[(philosopher->id + 1) % philo_nbr];
    }
	else 
	{
        philosopher->first_fork = &forks[(philosopher->id + 1) % philo_nbr];
        philosopher->second_fork = &forks[philosopher->id];
    }
}

/*
	EVEN ODD fork assignement
*/
// static void	ft_assign_fork(t_philospher *philo, t_fork *forks, int position)
// {
// 	int	philo_nbrs;

// 	philo_nbrs = philo->table->philo_nbr;
// 	// == positions
// 	philo->first_fork = &forks[(position + 1) % philo_nbrs];
// 	//      dead_lock
// 	philo->second_fork = &forks[(position)];
// 	if (philo->id % 2)
// 	{
// 		philo->first_fork = &forks[position];
// 		//      dead_lock
// 		philo->second_fork = &forks[(position + 1) % philo_nbrs];
// 	}
// }

void philo_init(t_table *table) 
{
	int i;

	i = 0;
    while (i < table->philo_nbr)
	{
        table->philos[i].id = i;
        table->philos[i].meals_cnt = 0;
        table->philos[i].full = false;
        table->philos[i].last_meal_time = 0;
        table->philos[i].table = table;
        assign_forks(&table->philos[i], table->fork, table->philo_nbr);
		i++;
	}
}


void	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->end_simaltions = false;
	table->all_thread_ready = false;
	table->thread_running_nbr = 0;
	table->philos = safe_malloc(sizeof(t_philospher) * table->philo_nbr);
	printf("Allocated memory for %ld philosophers\n", table->philo_nbr);
	safe_mutex_handle(&table->table_mutex, INIT);
	table->fork = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	//printf("the fork as been asign = %d\n", table->fork->fork_id);
	safe_mutex_handle(&table->write_mutex, INIT);
	while (++i < table->philo_nbr)
	{
		safe_mutex_handle(&table->fork[i].fork, INIT);
		table->fork[i].fork_id = i; // super pour debug
		printf(Y"Initialize fork %d\n"RST, i);
	}
	printf(Y"im done for assign the data i start to assign fork\n"RST);
	philo_init(table); // done
}
