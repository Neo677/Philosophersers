/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:07:07 by thobenel          #+#    #+#             */
/*   Updated: 2024/10/30 14:07:10 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	if the philo die :
	1) get th elast meal time (thread safe)
	2) temps ecouler ?
	3) check si le philo depasse
*/

bool	philo_died(t_philospher *philo)
{
	long	elapsed;
	long	last_meal;
	bool	is_full;

	last_meal = get_long(&philo->philo_mutex, &philo->last_meal_time);
	elapsed = getime(MILLISECONDS) - last_meal;
	is_full = get_bool(&philo->philo_mutex, &philo->full);
	if (is_full)
		return (false);
	if (elapsed >= philo->table->time_to_die)
		return (true);
	return (false);
}

/*
	0) spinlock wait all phil, synchro start
	1) set time last meal
	2) synchro with monitor increase a table variable counter,
		with all threads running
	(			algo =	 			)
			1) am i full ?
			2) eat
			3) sleep ->  write_status & precise usleep  ✅
			4) think
*/

void	*dinner_simulation(void *data)
{
	t_philospher	*philo;

	philo = (t_philospher *)data;
	wait_all_thread(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, getime(MILLISECONDS));
	increase_long(&philo->table->table_mutex,
		&philo->table->thread_running_nbr);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!simulation_finish(philo->table))
	{
		if (get_bool(&philo->philo_mutex, &philo->full))
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo);
	}
	return (NULL);
}

/*
	actual meat
	./philo 5 800 200 200 [5]

	0) if no meals, return (0)->w back to main
		0.1) if only one philo-> ad hoc fonction
	1) create all thread, all philo
	2) create a monitor thread -> dead emoji
	3) synchronise the beginning of the simulations
		pthread_create-> philo start running !
		every philo start simultaneoulsy
	4) join everyone
	5) now all the thread are ready !
	6) start the simualtions
	(if we manage to reach this line, all philo are full)
	(possible leak est fix je rejoint les threads philo et join Monitor aussi)
*/

void	dinner_start(t_table *table)
{
	int	i;

	if (table->nbr_limit_meal == 0)
		return ;
	else if (table->philo_nbr == 1)
		safe_thread_handle(&table->philos[0].thread_id,
			alone_philo, &table->philos[0], CREATE);
	else
	{
		i = -1;
		while (++i < table->philo_nbr)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation,
				&table->philos[i], CREATE);
	}
	safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE);
	table->start_simulation = getime(MILLISECONDS);
	set_bool(&table->table_mutex, &table->all_thread_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->end_simulations, true);
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}
