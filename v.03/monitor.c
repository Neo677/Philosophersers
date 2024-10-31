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

void	*monitor_dinner(void *data)
{
	t_table *table;

	table = (t_table *)data;
	while (!all_thread_running())// todo


	return (NULL);
}