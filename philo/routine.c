/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:54:40 by thobenel          #+#    #+#             */
/*   Updated: 2024/11/11 16:54:47 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philospher *philo)
{
	write_status(THINKING, philo, true);
	precise_usleep(philo->table->time_to_think, philo->table);
}


/*
	eat routine
	1) grab the fork : here seconde then first pair | 
							first then second impair
	2) eat : write eat, update last meal, update meal counter,
		eventually bool full
	3) release the forks
	4) incrémenter meals_cnt de manière (thread-safe)
	5) lacher les fouchette dans le sens inverse
*/

void	eat(t_philospher *philo)
{
	long	meals;

	take_fork(philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, getime(MILLISECONDS));
	increase_long(&philo->philo_mutex, &philo->meals_cnt);
	write_status(EATING, philo, true);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meal > 0)
	{
		meals = get_long(&philo->philo_mutex, &philo->meals_cnt);
		if (meals >= philo->table->nbr_limit_meal)
			set_bool(&philo->philo_mutex, &philo->full, true);
	}
	lache_fork(philo);
}