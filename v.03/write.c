/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:59:23 by thobenel          #+#    #+#             */
/*   Updated: 2024/10/30 15:59:25 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	same as write, just with more info helping when debugging
*/
static void	write_status_debug(t_philo_status status, t_philospher *philo, long elapsed)
{
	if (TAKE_FIRST_FORK == status && !simulation_finish(philo->table))
		printf(W "%6ld" RST " %d has taken the 1-first fork  " "\t\t\tn°" B "[  🍝 %d 🍝  ]\n" RST, elapsed, philo->id, philo->first_fork->fork_id);
	else if (TAKE_SECONDE_FORK == status && !simulation_finish(philo->table))
		printf(W "%6ld" RST " %d has taken the 2-first fork  " "\t\t\tn°" B "[  🍝 %d 🍝  ]\n" RST, elapsed, philo->id, philo->second_fork->fork_id);
	else if (EATING == status && !simulation_finish(philo->table))
		printf(W "%6ld" C " %d his eating" "\t\t\t" Y "[  🍝   %ld  🍝  ]\n" RST, elapsed, philo->id, philo->meals_cnt);
	else if (SLEEPING == status && !simulation_finish(philo->table))
		printf(W"%6ld"RST" &d is sleeping   😴  leave him some intimitate !\n", elapsed, philo->id);
	else if (THINKING == status && !simulation_finish(philo->table))
		printf(W"%6ld"RST" &d is thinking 🤔 \n", elapsed, philo->id);
	else if (DIED == status)
		printf(RED"\t\t 💀 %6ld %d died 💀 \n"RST, elapsed, philo->id);
}


/* theory
	[time_ms] [philo_id] [action]
	thread safe
		write mutex
*/

/* plans
	fonction to write the philo status 
	in a thread safe manner :
	(emoji locker) write
	(emoji locker) philo's mutex to read meal counter
	(emoji locker) table lock to read if end_simalutions
*/

void	write_status(t_philo_status status, t_philospher *philo, bool debug)
{
	long elapsed;

	elapsed = getime(MILLISECONDS) - philo->table->start_simulation;

	if (philo->full) // T
		return ;
	
	// locker
	safe_mutex_handle(&philo->table->write_mutex, LOCK);

	if (debug)
		write_status_debug(status, philo, elapsed); // todo
	else
	{

		if (((TAKE_FIRST_FORK == status) || (TAKE_SECONDE_FORK == status)) && !simulation_finish(philo->table))
			printf(W"%-6ld"RST" %d has taken a fork 🍴 \n", elapsed, philo->id);
		else if (EATING == status && !simulation_finish(philo->table))
			printf(W"%-6ld"C"[  🍝  %d his eating ! 🍝  ] \n"RST, elapsed, philo->id);
		else if (SLEEPING == status && !simulation_finish(philo->table))
			printf(W"%-6ld"RST" %d his sleeping 😴 leave him some intimitate ! \n", elapsed, philo->id);
		else if (THINKING == status && !simulation_finish(philo->table))
			printf(W"%-6ld"RST"[ 🤔 %d his thinking ! 🤔 ]\n", elapsed, philo->id);
		else if (DIED == status)
			printf(RED"%-6ld  [💀  %d died 💀 ]\n"RST, elapsed, philo->id);
	}

	// unlock
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}

