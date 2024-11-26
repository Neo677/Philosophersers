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
theory :
	[time_ms] [philo_id] [action]
	thread safe
	write mutex
		plans :
		fonction to write the philo status 
		in a thread safe manner :
		write
		philo's mutex to read meal counter
		table lock to read if end_simalution  */

void	ft_w_death(t_philo_status status, t_philospher *philo, long ecouler)
{
	if (status == DIED && !simulation_finish(philo->table))
		printf(RED"\t\t 💀 %6ld %d died 💀 \n"RST, ecouler, philo->id);
}

void	write_status(t_philo_status status, t_philospher *philo)
{
	long	ecouler;

	ecouler = getime(MILLISECONDS) - philo->table->start_simulation;
	if (philo->full)
		return ;
	else
	{
		safe_mutex_handle(&philo->table->write_mutex, LOCK);
		if (TAKE_FIRST_FORK == status && !simulation_finish(philo->table))
			ft1_fork(status, philo, ecouler);
		else if (TAKE_SECOND_FORK == status && !simulation_finish(philo->table))
			ft2_fork(status, philo, ecouler);
		else if (EATING == status && !simulation_finish(philo->table))
			ft_w_eating(status, philo, ecouler);
		else if (SLEEPING == status && !simulation_finish(philo->table))
			ft_w_sleeping(status, philo, ecouler);
		else if (THINKING == status && !simulation_finish(philo->table))
			ft_w_thinking(status, philo, ecouler);
		else if (DIED == status)
			ft_w_death(status, philo, ecouler);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
