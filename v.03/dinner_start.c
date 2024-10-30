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
	0) wait all phil, synchro start

	1) endless loop philo
*/

void	*dinner_simulation(void *data)
{
	t_philospher *philo;

	philo = (t_philospher *)data;
	//	spinlock
	wait_all_thread(philo->table); // todo

	// set last meal time
	while (!simulation_finish(philo->table))
	{
		// 1) am i full ?
		if (philo->full) // todo thread safe ?
			break;

		// 2) eat
		eat(philo);

		// 3) sleep  ->write_status & precise usleep
		write_status(phi, t_philospher *philo, bool debug);

		// 4) think
			thinking(philo); // todo
		
	}



	return (NULL);
}

/*
	actual meat 

	./philo 5 800 200 200 [5]

	0) if no meals, return (0)
		0.1) if only one philo-> ad hoc fonction
	1) create all thread, all philo
	2) create a monitor thread -> dead emoji
	3) synchronise the beginning of the simulations
		pthread_create-> philo start running !
		every philo start simultaneoulsy
	4) join everyone
*/

void	dinner_start(t_table *table)
{
	int i;

	i = -1;
	if (table->nbr_limit_meal == 0)
		return ; // back to main, clean
	else if (table->philo_nbr == 1)
		; // todo
	else
	{
		while (i++ < table->philo_nbr)
			safe_thread_handle(table->philos[i].thread_id, dinner_simulation, &table->philos[i], CREATE);
	}

	// start of simulations
	table->start_simulation = get_time(MILLISECONDS);


	// now all the thread are ready !
	set_bool(table->table_mutex, table->all_thread_ready, true);

	//	Wait for everyone 
	i = -1;
	while(++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);

	// if we manage to reach this line, all philo are full

}