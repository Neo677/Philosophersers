/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:47:37 by thobenel          #+#    #+#             */
/*   Updated: 2024/10/31 14:47:38 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	time to die = last meal__________last meal
	1) Attendre que tous les threads soient prêts
	2) Vérifier si un philosophe est mort
	3) Afficher le message de décès
	4) Vérifier si tous les philosophes sont full
*/

static void	ft_wait_for_them(t_table *table)
{
	while (!all_thread_running(&table->table_mutex,
			&table->thread_running_nbr, table->philo_nbr))
		usleep(100);
}

static bool	ft_check_is_death(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		if (philo_died(&table->philos[i]))
		{
			write_status(DIED, &table->philos[i], true);
			set_bool(&table->table_mutex, &table->end_simulations, true);
			return (true);
		}
	}
	return (false);
}

static bool	ft_check_is_full(t_table *table)
{
	if (table->nbr_limit_meal > 0 && all_philo_full(table))
	{
		set_bool(&table->table_mutex, &table->end_simulations, true);
		return (true);
	}
	return (false);
}

void	*monitor_dinner(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	ft_wait_for_them(table);
	i = -1;
	while (!simulation_finish(table))
	{
		if (ft_check_is_death(table) || ft_check_is_full(table))
			break ;
		usleep(5000);
	}
	return (NULL);
}
