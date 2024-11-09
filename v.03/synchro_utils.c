/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:39:08 by thobenel          #+#    #+#             */
/*   Updated: 2024/10/30 14:39:10 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* SPINLOCK to synchronize philos start */

void wait_all_thread(t_table *table)
{
    printf("Début de l'attente de synchronisation des threads\n");
    while (!get_bool(&table->table_mutex, &table->all_thread_ready)) {
        ;  // Pause légère pour éviter un blocage CPU
    }
    printf("Tous les threads sont prêts\n");
}

// Monitor busy wait until all threads are running 
bool all_thread_running(t_mutex *mutex, long *threads, long philo_nbr)
{
    bool res;
	
	res = false;
    safe_mutex_handle(mutex, LOCK);
    if (*threads == philo_nbr) 
	{
        res = true;
        printf("Tous les philosophes sont prêts (%ld/%ld).\n", *threads, philo_nbr);
    } 
	else 
	{
        printf("En attente des philosophes : %ld/%ld prêts.\n", *threads, philo_nbr);
    }
    safe_mutex_handle(mutex, UNLOCK);
    return (res);
}
// Increase thread running count to synchronize with the monitor 


void increase_long(t_mutex *mutex, long *value)
{
    safe_mutex_handle(mutex, LOCK);
    (*value)++;
    printf("Nombre de threads actifs mis à jour : %ld\n", *value);
    safe_mutex_handle(mutex, UNLOCK);
}
