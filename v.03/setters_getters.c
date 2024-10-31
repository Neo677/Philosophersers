/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters_getters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:27:23 by thobenel          #+#    #+#             */
/*   Updated: 2024/10/30 14:27:25 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Module containing setters_getter
	to avoid writting LOCK and UNLOCK everywhere
*/

//		BOOL
void	set_bool(t_mutex *mutex, bool *dest, bool value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

bool	get_bool(t_mutex *mutex, bool *value)
{
	bool res;

	safe_mutex_handle(mutex, LOCK);
	// Reading thread safe
	res = *value;
	safe_mutex_handle(mutex, UNLOCK);
	return (res);
}

//		LONG
long get_long(t_mutex *mutex, long *value)
{
	long res;

	safe_mutex_handle(mutex, LOCK);
	res = *value;
	safe_mutex_handle(mutex, UNLOCK);
	return (res);
}

void	set_long(t_mutex *mutex, long *dest, long value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

/*
	REDONDANT ?? nahhh
*/

bool	simulation_finish(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simaltions));
}