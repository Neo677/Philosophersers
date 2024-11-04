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

/*
	EVEN ODD fork assignement
*/
static void	ft_assign_fork(t_philospher *philo, t_fork *forks, int position)
{
	int	philo_nbrs;

	philo_nbrs = philo->table->philo_nbr;
	// == positions
	philo->first_fork = &forks[(position + 1) % philo_nbrs];
	//      dead_lock
	philo->second_fork = &forks[(position)];
	if (philo->id % 2)
	{
		philo->first_fork = &forks[position];
		//      dead_lock
		philo->second_fork = &forks[(position + 1) % philo_nbrs];
	}
}

static void	philo_init(t_table *table)
{
	int				i;
	t_philospher	*philo;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i;
		philo->full = false;
		philo->meals_cnt = 0;
		philo->table = table;
		safe_mutex_handle(&philo->philo_mutex, INIT);
		
		// AD hoc 		i position in the table
		ft_assign_fork(philo, table->fork, i);
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
	printf("Allocated memory for %ld philosophers\n", table->philo_nbr);
	safe_mutex_handle(&table->write_mutex, INIT);
	while (++i < table->philo_nbr)
	{
		safe_mutex_handle(&table->fork[i].fork, INIT);
		table->fork[i].fork_id = i; // super pour debug
		printf(Y"Initialize fork %d\n"RST, i);
	}
	philo_init(table); // done
}
