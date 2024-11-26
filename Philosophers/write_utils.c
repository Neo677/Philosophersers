/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:47:36 by thobenel          #+#    #+#             */
/*   Updated: 2024/11/22 17:22:21 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_w_thinking(t_philo_status status, t_philospher *philo, long ecouler)
{
	if (status == THINKING && !simulation_finish(philo->table))
		printf(W"%6ld"Y" %d is thinking \n", ecouler, philo->id);
}

void	ft_w_sleeping(t_philo_status status, t_philospher *philo, long ecouler)
{
	if (status == SLEEPING && !simulation_finish(philo->table))
		printf(W"%6ld"B" %d is sleeping 😴 leave him some intimitate !\n",
			ecouler, philo->id);
}

void	ft_w_eating(t_philo_status status, t_philospher *philo, long ecouler)
{
	if (status == EATING && !simulation_finish(philo->table))
		printf(W "%6ld" C " %d his eating" "\t\t\t" Y
			"[  🍝   %ld  🍝  ]\n" RST, ecouler, philo->id, philo->meals_cnt);
}

void	ft1_fork(t_philo_status status, t_philospher *philo, long ecouler)
{
	if (status == TAKE_FIRST_FORK && !simulation_finish(philo->table))
		printf(W "%6ld" RST " %d has taken the 1-first fork  " "\t\t\tn°"
			B "[  🍝 %d 🍝  ]\n" RST, ecouler, philo->id,
			philo->first_fork->fork_id);
}

void	ft2_fork(t_philo_status status, t_philospher *philo, long ecouler)
{
	if (status == TAKE_SECOND_FORK && !simulation_finish(philo->table))
		printf(W "%6ld" RST " %d has taken the 2-first fork  " "\t\t\tn°"
			B "[  🍝 %d 🍝  ]\n" RST, ecouler, philo->id,
			philo->second_fork->fork_id);
}
