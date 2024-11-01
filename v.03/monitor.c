/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:47:37 by thobenel          #+#    #+#             */
/*   Updated: 2024/10/31 14:47:38 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
				t_die
	last meal_______________last meal
*/
static bool philo_died(t_philospher *philo)
{
	long elapsed;
	long time_to_die_bitch;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return(false);
	elapsed = getime(MILLISECONDS) - get_long(&philo->philo_mutex, &philo->last_meal_time);
	time_to_die_bitch = philo->table->time_to_die / 1e3;

	if ( elapsed > time_to_die_bitch)
		return (true);
	return (elapsed > time_to_die_bitch);
}

void	*monitor_dinner(void *data)
{
	t_table *table;
	int i;

	table = (t_table *)data;
	// wait all thread to be ready
	while (!all_thread_running(&table->table_mutex,&table->thread_running_nbr, table->philo_nbr)) // done
	{
		;
	}
	while (!simulation_finish(table))
	{
		// cheking si the elaps time of the philosopher is major than time_to_die ??
		i = -1;
		while(++i < table->philo_nbr)
		{
			if (philo_died(table->philos + i)) // done
			{
				set_bool(&table->table_mutex, &table->end_simaltions, true);
				write_status(DIED, table->philos + i, DEBUG_MODE);
				break;
			}
		}
		usleep(1000);
	}
	return (NULL);
}