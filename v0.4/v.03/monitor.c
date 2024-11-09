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
				t_die
	last meal_______________last meal
*/

void *monitor_dinner(void *data)
{
    t_table *table = (t_table *)data;
    int i;

    // Attendre que tous les threads soient prêts
    while (!all_thread_running(&table->table_mutex, &table->thread_running_nbr, table->philo_nbr))
        usleep(100);

    while (!simulation_finish(table))
    {
        // Vérifier si tous les philosophes sont full
        if (table->nbr_limit_meal > 0 && all_philo_full(table))
        {
            set_bool(&table->table_mutex, &table->end_simulations, true);
            break;
        }

        // Vérifier si un philosophe est mort
        i = 0;
        while (i < table->philo_nbr)
        {
            if (philo_died(&table->philos[i]))
            {
                // Afficher le message de décès
                write_status(DIED, &table->philos[i], true);
                set_bool(&table->table_mutex, &table->end_simulations, true);
                break;
            }
            i++;
        }
        usleep(1000);
    }
    return NULL;
}
