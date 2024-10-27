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

typedef struct s_define_arg
{
	int total;
	int die;
	int eat;
	int sleep;
	int m_eat;
	lont int start_t;

	pthread_mutex_t	write_mutex;
	pthread_mutex_t dead;
	pthread_mutex_t time_eat;
	pthread_mutex_t	finish;
	int nb_philo_finish;
	int stop;

	/*pthread_t	thread;
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
	pthread_mutex_t *meal_lock;*/
}				t_define_arg;

typedef struct s_philosopher
{
	int id;
	pthread_t		id_thread;
	pthread_t		thread_death_id;
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;
	t_define_arg		*pa;
	long int 		ms_eat;
	unsigned int 		nb_eat;
	int finish;

	/*int 			dead_flag;
	pthread_mutex_t dead_lock;
	pthread_mutex_t meal_lock;
	pthread_mutex_t write_lock;
	t_philo 		*philos;*/
}					t_philosopher;

typedef struct s_what_philo
{
	t_philosopher *ph;
	t_define_arg a;
}				t_what_philo

int stop(t_philosopher *philo);
int ft_exit(char *str);
int check_death(t_philosopher *philo);



#endif