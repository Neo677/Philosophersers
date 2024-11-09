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
		;
	return (NULL);
}


void sleeping(t_philospher *philo)
{
    write_status(SLEEPING, philo, true);  // Indique que le philosophe est en train de dormir
    precise_usleep(philo->table->time_to_sleep, philo->table);  // Délai de sommeil
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
    long meals;

    // Prendre les fourchettes
    safe_mutex_handle(&philo->first_fork->fork, LOCK);
    write_status(TAKE_FIRST_FORK, philo, true);
    safe_mutex_handle(&philo->second_fork->fork, LOCK);
    write_status(TAKE_SECOND_FORK, philo, true);

    // Mettre à jour le temps du dernier repas
    set_long(&philo->philo_mutex, &philo->last_meal_time, getime(MILLISECONDS));

    // Manger
    write_status(EATING, philo, true);
    precise_usleep(philo->table->time_to_eat, philo->table);

    // Mettre à jour le nombre de repas
    increase_long(&philo->philo_mutex, &philo->meals_cnt);
    if (philo->table->nbr_limit_meal > 0)
    {
        meals = get_long(&philo->philo_mutex, &philo->meals_cnt);
        if (meals >= philo->table->nbr_limit_meal)
            set_bool(&philo->philo_mutex, &philo->full, true);
    }

    // Relâcher les fourchettes
    safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
    safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

void	*philo_life(void *arg)
{
    t_philospher *philo = (t_philospher *)arg;

    printf("Philosophe %d a démarré sa routine\n", philo->id);

    while (!simulation_finish(philo->table)) {
        printf("Philosophe %d pense\n", philo->id);
        thinking(philo);
        
        // Temporairement désactivé pour tester
        // printf("Philosophe %d va manger\n", philo->id);
        // eat(philo);
        
        printf("Philosophe %d va dormir\n", philo->id);
        sleeping(philo);
    }
    
    printf("Philosophe %d a terminé sa routine\n", philo->id);
    return (NULL);
}

/*
	1) wait all philo, and synchro start
	2) endlees thinkings loop philo
*/
void *dinner_simulation(void *data)
{
	t_philospher *philo;
	long full_full;

	philo = (t_philospher *)data;

	// spinlock
	wait_all_thread(philo->table);

	// set time last meal
	set_long(&philo->philo_mutex, &philo->last_meal_time, getime(MILLISECONDS));

	// synchro with monitor
	// increase a table variable counter, with all threads running
	increase_long(&philo->table->table_mutex, &philo->table->thread_running_nbr);

	// set last meal time ??

	while (!simulation_finish(philo->table))
	{
		// 1) am i full ?
		get_bool(&philo->philo_mutex, &philo->full); // todo thread safe ?
		if (full_full)
			break;

		// 2) eat
		eat(philo);

		// 3) sleep  ->  write_status & precise usleep  ✅
		write_status(SLEEPING, philo, true);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		// usleep(philo->table->time_to_sleep);
		printf("%-d im awake \n", philo->id);
		// 4) think
		thinking(philo); // todo
	}

	return NULL;
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

void dinner_start(t_table *table)
{
    int i;

    i = -1;
    if (table->nbr_limit_meal == 0)
        return;
    else if (table->philo_nbr == 1) 
	{
        printf("Lancement du philosophe seul 😢\n");
        safe_thread_handle(&table->philos[0].thread_id, alone_philo, &table->philos[0], CREATE);
    }
	else 
	{
		i = 0;
        while (i < table->philo_nbr) 
		{
            printf("Création du thread pour le philosophe %d\n", i);
            safe_thread_handle(&table->philos[i].thread_id, philo_life, &table->philos[i], CREATE);
            printf("Thread du philosophe %d créé avec succès\n", i);
			i++;
        }
    }
    
    // Créer un thread pour surveiller la simulation
    printf("Création du thread de surveillance\n");
    safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE);
    printf("Thread de surveillance créé avec succès\n");

    // Début de la simulation
    table->start_simulation = getime(MILLISECONDS);
    set_bool(&table->table_mutex, &table->all_thread_ready, true);

    printf("Début de la simulation\n");

    // Attendre que tous les philosophes terminent leur routine
    i = -1;
    while (++i < table->philo_nbr) {
        printf("Attente de la fin du thread pour le philosophe %d\n", i);
        safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
        printf("Thread du philosophe %d terminé\n", i);
    }

    set_bool(&table->table_mutex, &table->end_simaltions, true);
    printf("Fin de la simulation\n");
}

/*void	dinner_start(t_table *table)
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
	safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE);

	// start of simulations
	table->start_simulation = getime(MILLISECONDS);

	// now all the thread are ready !
	set_bool(&table->table_mutex, &table->all_thread_ready, true);

	// Wait for everyone 
	i = -1;
	while(++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);

	// if we manage to reach this line, all philo are full
	set_bool(&table->table_mutex, &table->end_simaltions, true);
}*/


/*
	Need to implement a fonction that check if the phil_nbr is odd or even if its odd (impair) and 
	implemenet the routine eat think sleep on this we keep the same system that we already got
*/