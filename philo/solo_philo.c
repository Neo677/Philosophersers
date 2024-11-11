/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:57:27 by thobenel          #+#    #+#             */
/*   Updated: 2024/11/11 16:57:29 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	same algo but...
	1) fake lock the fork
	2) sleep until the monitor will bust it
	3)Synchronisation initiale
	4)Enregistrement du temps du dernier repas
	5)Indiquer que le thread est en cours d'exécution
	6)Prendre la première fourchette
	7)Attendre le temps pour mourir
	8)Philosophe meurt
	9)Libérer la fourchette
	10)Indiquer la fin de la simulation
*/

void	*alone_philo(void *arg)
{
	t_philospher	*philo;

	philo = (t_philospher *)arg;
	printf("enter in alone_philo\n");
	wait_all_thread(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, getime(MILLISECONDS));
	increase_long(&philo->table->table_mutex,
		&philo->table->thread_running_nbr);
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, true);
	precise_usleep(philo->table->time_to_die, philo->table);
	write_status(DIED, philo, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	set_bool(&philo->table->table_mutex, &philo->table->end_simulations, true);
	return (NULL);
}