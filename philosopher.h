/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:56:10 by thobenel          #+#    #+#             */
/*   Updated: 2024/10/23 20:56:11 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILOSPHER_H
# define PHILOSPHER_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#include "libft/libft.h"


//gcc -pthread main.c

typedef struct s_philo
{
	pthread_t	thread;
	
	int id;
	int ending;
	int repas_manger;

	size_t dernier_repas;
	size_t time_die;
	size_t time_eat;
	size_t time_sleep;
	size_t start_time;

	int number_of_philo;
	int	number_time_to_eat;
	int *dead;

	pthread_mutex_t *r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t *write_lock;
	pthread_mutex_t *meal_lock;
}							t_philo;

typedef struct s_program
{
	int 			dead_flag;
	pthread_mutex_t dead_lock;
	pthread_mutex_t meal_lock;
	pthread_mutex_t write_lock;
	t_philo *philos;
}					t_program;

#endif