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

void	wait_all_thread(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_thread_ready))
		;
}

// Monitor busy wait until all threads are running 

bool 	all_thread_running(t_mutex *mutex, long *threads, long philo_nbr)
{
	bool res;

	res = false;
	safe_mutex_handle(mutex, LOCK);
	if (*threads == philo_nbr)
		res = true;
	safe_mutex_handle(mutex, UNLOCK);
	// Guarantees that no other function modifies *threads during the check, thus avoiding data races.

	return (res);
}

// Increase thread running count to synchronize with the monitor 
void	increase_long(t_mutex *mutex, long *value)
{
	safe_mutex_handle(mutex, LOCK);
	(*value)++;
	safe_mutex_handle(mutex, UNLOCK);
}

