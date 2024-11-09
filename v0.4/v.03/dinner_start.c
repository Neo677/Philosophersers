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
bool philo_died(t_philospher *philo)
{
	long elapsed;
	long last_meal;
	bool is_full;

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
	same algo but...
	1) fake lock the fork
	2) sleep until the monitor will bust it
*/
void	*alone_philo(void *arg)
{
    t_philospher *philo;

    philo = (t_philospher *)arg;

    // Synchronisation initiale
    wait_all_thread(philo->table);

    // Enregistrement du temps du dernier repas
    set_long(&philo->philo_mutex, &philo->last_meal_time, getime(MILLISECONDS));

    // Indiquer que le thread est en cours d'exécution
    increase_long(&philo->table->table_mutex, &philo->table->thread_running_nbr);

    // Prendre la première fourchette
    safe_mutex_handle(&philo->first_fork->fork, LOCK);
    write_status(TAKE_FIRST_FORK, philo, true);

    // Attendre le temps pour mourir
    precise_usleep(philo->table->time_to_die, philo->table);

    // Philosophe meurt
    write_status(DIED, philo, true);

    // Libérer la fourchette
    safe_mutex_handle(&philo->first_fork->fork, UNLOCK);

    // Indiquer la fin de la simulation
    set_bool(&philo->table->table_mutex, &philo->table->end_simulations, true);

    return (NULL);
}

// 				done 
static void thinking(t_philospher *philo)
{
	write_status(THINKING, philo, true);
	precise_usleep(philo->table->time_to_think, philo->table);
}

/*
	eat routine 
	1) grab the fork : here first & seconde fork is hand | i dont worry about left right
	2) eat : write eat, update last meal, update meal counter, eventually bool full
	3) release the forks
*/

static void eat(t_philospher *philo)
{
    long meals;

    if (philo->id % 2 == 0)
    {
        // Philosophes pairs
        safe_mutex_handle(&philo->second_fork->fork, LOCK);
        write_status(TAKE_SECOND_FORK, philo, true);
        safe_mutex_handle(&philo->first_fork->fork, LOCK);
        write_status(TAKE_FIRST_FORK, philo, true);
    }
    else
    {
        // Philosophes impairs
        safe_mutex_handle(&philo->first_fork->fork, LOCK);
        write_status(TAKE_FIRST_FORK, philo, true);
        safe_mutex_handle(&philo->second_fork->fork, LOCK);
        write_status(TAKE_SECOND_FORK, philo, true);
    }

    // 2) Manger
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

    // 3) Relâcher les fourchettes
    safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
    safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

/*
static void eat(t_philospher *philo)
{
	long meals;

	// 1)
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, true);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, true);

	// 2)
	set_long(&philo->philo_mutex, &philo->last_meal_time, getime(MILLISECONDS));
	increase_long(&philo->philo_mutex, &philo->meals_cnt); // incrémenter meals_cnt de manière (thread-safe)
	write_status(EATING, philo, true);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meal > 0)
	{
		meals = get_long(&philo->philo_mutex, &philo->meals_cnt);
		if (meals >= philo->table->nbr_limit_meal)
		{
			set_bool(&philo->philo_mutex, &philo->full, true);
		}
	}	

	// 3)
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}
*/


/*
	0) wait all phil, synchro start

	1) endlesthinkings loop philo
*/

void	*dinner_simulation(void *data)
{
	t_philospher *philo;
	bool really_full;

	philo = (t_philospher *)data;

	//	spinlock
	wait_all_thread(philo->table); // done

	// set time last meal
	set_long(&philo->philo_mutex, &philo->last_meal_time, getime(MILLISECONDS));

	// synchro with monitor 
	// increase a table variable counter, with all threads running 
	// done
	increase_long(&philo->table->table_mutex, &philo->table->thread_running_nbr);

	if (philo->id % 2 == 0)
		usleep(200);
	
	// set last meal time ??
	while (!simulation_finish(philo->table))
	{
		// 1) am i full ? 
		really_full = get_bool(&philo->philo_mutex, &philo->full);
		if (really_full) //  thread safe ?
			break;
			
		// 2) eat
		eat(philo);

		// 3) sleep  ->  write_status & precise usleep  ✅
		write_status(SLEEPING, philo, true);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		// 4) think
		thinking(philo); // done
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
		safe_thread_handle(&table->philos[0].thread_id, alone_philo, &table->philos[0], CREATE); // done
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
	set_bool(&table->table_mutex, &table->end_simulations, true);

}


bool	all_philo_full(t_table *table)
{
	int i;

	i = 0;
	while(i < table->philo_nbr)
	{
		if (!get_bool(&table->philos[i].philo_mutex, &table->philos[i].full))
			return (false);
		i++;
	}
	return (true);
}