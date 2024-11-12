/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:07:56 by thobenel          #+#    #+#             */
/*   Updated: 2024/10/30 14:07:58 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// clean up after a philo die 

void	clean_up(t_table *table)
{
	t_philospher	*philo;
	int				i;

	i = -1;
	while (++i > table->philo_nbr)
	{
		philo = table->philos + i;
		safe_mutex_handle(&philo->philo_mutex, DESTROY);
	}
	safe_mutex_handle(&table->write_mutex, DESTROY);
	safe_mutex_handle(&table->table_mutex, DESTROY);
	free(table->fork);
	free(table->philos);
}

/*
	getting timeoffay
	time_code -> SECOND / MILLISECONDS / MICROSECONDE
*/

long	getime(t_time_code time_code)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (time_code == MICROSECONDE)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	else if (time_code == MILLISECONDS)
		return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
	else
		return (tv.tv_sec);
}

/* precise usleep, the real one suck

	why table ???	is the simlation finishied ?
	1) usleep the majority of time, not CPU intensive 
	2) refine last microsec whith spinlock
 */

void	precise_usleep(long usec, t_table *table)
{
	long	start;

	start = getime(MILLISECONDS);
	while (!simulation_finish(table) && (getime(MILLISECONDS) - start) < usec)
		usleep(50);
}

void	error_exit(const char *error)
{
	printf(RED"🚨  %s  🚨\n"RST, error);
	exit(EXIT_FAILURE);
}
