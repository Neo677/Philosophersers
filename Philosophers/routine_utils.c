/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:55:53 by thobenel          #+#    #+#             */
/*   Updated: 2024/11/11 16:55:55 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philospher *philo)
{
	if (philo->id % 2 == 0)
	{
		safe_mutex_handle(&philo->second_fork->fork, LOCK);
		write_status(TAKE_SECOND_FORK, philo);
		safe_mutex_handle(&philo->first_fork->fork, LOCK);
		write_status(TAKE_FIRST_FORK, philo);
	}
	else
	{
		safe_mutex_handle(&philo->first_fork->fork, LOCK);
		write_status(TAKE_FIRST_FORK, philo);
		safe_mutex_handle(&philo->second_fork->fork, LOCK);
		write_status(TAKE_SECOND_FORK, philo);
	}
}

void	lache_fork(t_philospher *philo)
{
	if (philo->id % 2 == 0)
	{
		safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
		safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
	}
	else
	{
		safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
		safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	}
}

bool	all_philo_full(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (!get_bool(&table->philos[i].philo_mutex, &table->philos[i].full))
			return (false);
		i++;
	}
	return (true);
}
