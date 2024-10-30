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
}