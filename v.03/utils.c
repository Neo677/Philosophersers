/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:07:56 by thobenel          #+#    #+#             */
/*   Updated: 2024/10/30 14:07:58 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	getting timeoffay

	time_code -> SECOND / MILLISECONDS / MICROSECONDE
*/
long getime(t_time_code time_code)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL));
		error_exit("Gettimeofday failed");
	if (SECOND == time_code)
		return (tv.tv_sec + (tv.tv_usec / 1e6)); // convertion basic mathematique en 
	else if (MILLISECONDS == time_code)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (MICROSECONDE == time_code)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("Wrong input to gettime!");
	return (1337);
	
}

/* precise usleep, the real one suck

	why table ???	is the simlation finishied ?
	1) usleep the majority of time, not CPU intensive 
	2) refine last microsec whith spinlock

 */

void	precise_usleep(long usec, t_philospher *philo)
{
	long start;
	long elapsed;
	long rem;

	start = getime(MICROSECONDE);
	while (getime(MICROSECONDE) - start < usec)
	{
		// 1) 
		if (simulation_finish(philo->table))
			break;
		elapsed = getime(MICROSECONDE) - start;
		rem = usec - elapsed;

		// to get a spinclock threshold
		if (rem > 1e3)
			usleep(usec / 2);
		else
		{
			// SPINLOCK
			while (getime(MICROSECONDE) - start < usec)
				;

		}

	}

}

void    error_exit(const char *error)
{
    printf(RED"🚨  %s  🚨\n"RST, error);
    exit(EXIT_FAILURE);
}

