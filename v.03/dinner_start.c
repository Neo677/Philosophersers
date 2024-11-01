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
	same algo but...
	1) fake lock the fork
	2) sleep until the monitor will bust it
*/
void	*alone_philo(void *arg)
{
	t_philospher *philo;

	philo = (t_philospher *)arg;
	wait_all_thread(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, getime(MILLISECONDS));
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while(!simulation_finish(philo->table))
		usleep(200);
	return (NULL);
}


// 				TODO finished
static void thinking(t_philospher *philo)
{
	write_status(THINKING, philo, DEBUG_MODE);
}

/*
	eat routine 
	1) grab the fork : here first & seconde fork is hand | i dont worry about left right
	2) eat : write eat, update last meal, update meal counter, eventually bool full
	3) release the forks
*/

static void eat(t_philospher *philo)
{
	// 1)
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECONDE_FORK, philo, DEBUG_MODE);

	// 2)
	set_long(&philo->philo_mutex, &philo->last_meal_time, getime(MILLISECONDS));
	philo->meals_cnt++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meal > 0 && philo->meals_cnt == philo->table->nbr_limit_meal)
	{
		set_bool(&philo->philo_mutex, &philo->full, true);
	}
	// 3)
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}


/*
	0) wait all phil, synchro start

	1) endlesthinkings loop philo
*/

void	*dinner_simulation(void *data)
{
	t_philospher *philo;

	philo = (t_philospher *)data;

	//	spinlock
	wait_all_thread(philo->table); // todo

	// set time last meal
	set_long(&philo->philo_mutex, &philo->last_meal_time, getime(MILLISECONDS));

	// synchro with monitor 
	// increase a table variable counter, with all threads running 
	// todo
	increase_long(&philo->table->table_mutex, &philo->table->thread_running_nbr);

	// set last meal time ??


	while (!simulation_finish(philo->table))
	{
		// 1) am i full ? 
		if (philo->full) // todo thread safe ?
			break;
			
		// 2) eat
		eat(philo);

		// 3) sleep  ->  write_status & precise usleep  ✅
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		
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
		safe_thread_handle(&table->philos[0].thread_id, alone_philo, &table->philos[0], CREATE); // todo
	else
	{
		while (++i < table->philo_nbr)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation, &table->philos[i], CREATE);
	}
	// monitor (💀)
										// done
	safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE);

	// start of simulations
	table->start_simulation = getime(MILLISECONDS);


	// now all the thread are ready !
	set_bool(&table->table_mutex, &table->all_thread_ready, true);

	//	Wait for everyone 
	i = -1;
	while(++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);

	// if we manage to reach this line, all philo are full
	set_bool(&table->table_mutex, &table->end_simaltions, true);

}