/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:07:29 by thobenel          #+#    #+#             */
/*   Updated: 2024/10/30 14:07:31 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

/* 	ANSI sequence pour output avec de jolie couleur */
/* Usage : 
    printf(RED "this is red text.", RST);
    printf(BLUE "this is blue text.", RST);

    Ne pas oublier de RST (reset) la couleur apres affichage
*/

# define RST  "\33[0m"
# define RED "\33[1;31m"       
# define G "\33[1;32m"
# define Y "\33[1;33m"
# define B "\33[1;34m"
# define M "\33[1;35m"
# define C "\33[1;36m"
# define W "\33[1;37m"

// /*	 	write fonction macro pour affichage en debug */
// # define DEBUG_MODE 0

/*		Philo Status    */
typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}			t_philo_status;

/*	OPCODE for mutex et thread fonction		*/

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}		t_opcode;

/* code for get time */

typedef enum e_time
{
	SECOND,
	MILLISECONDS,
	MICROSECONDE,
}			t_time_code;

typedef pthread_mutex_t	t_mutex;

typedef struct s_fork
{
	t_mutex	fork;
	int		fork_id;
}		t_fork;

//          structure
typedef struct s_table	t_table;

/*
	long last_meal_time = temps passer depuis le dernier repas ⏱️
	t_fork *first_fork = ODD assignement
    t_fork *second_fork = EVEN assignement
    pthread_t thread_id = un philo est un thread
    t_mutex philo_mutex = useful for races with the monitor
*/

typedef struct s_philospher
{
	int			id;
	long		meals_cnt;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mutex		philo_mutex;
	t_table		*table;
}		t_philospher;

/*
	table
   				input = ./philo 5 800 200 200 [5]
    long	philo_nbr =  ./philo '5'
    long    time_to_die =  ./philo 5 '800'
    long    time_to_eat =  ./philo 5 800 '200' 
    long    time_to_sleep =  ./philo 5 800 200 '200'
    long    nbr_limit_meal =  '[5]' |flag if -1
    long    start_simulation =  ⏱️
    bool    end_simulations =  un philo meurt 💀 ou que tout les philo sont full 🍝
	bool 	all_thread_ready =  synchro philo
	t_mutex table_mutex =  avoid race wile reading from table
*/

typedef struct s_table
{
	long			philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_think;
	long			nbr_limit_meal;
	long			start_simulation;
	bool			end_simulations;
	bool			all_thread_ready;
	long			thread_running_nbr;
	pthread_t		monitor;
	t_mutex			table_mutex;
	t_mutex			write_mutex;
	t_fork			*fork;
	t_philospher	*philos;
}		t_table;

/*					starting the dinner simulations				*/
bool	philo_died(t_philospher *philo);
void	*dinner_simulation(void *data);
void	dinner_start(t_table *table);

/*						init									*/
void	data_init(t_table *table);

/* 						monitoring (reste au aguet)				*/
void	*monitor_dinner(void *data);

/*						utils for philo							*/
bool	all_philo_full(t_table *table);
void	take_fork(t_philospher *philo);
void	lache_fork(t_philospher *philo);

/* 						routine for philo						*/
void	thinking(t_philospher *philo);
void	eat(t_philospher *philo);

/*						safe fonction							*/
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(t_mutex *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
			void *data, t_opcode opcode);

/* 						utils									*/
void	error_exit(const char *error);
void	parse_input(t_table *table, char **av);

/* 						parsing utils							*/
int		ft_is_digit(char c);
int		ft_is_space(char c);
int		ft_is_valid_input(char c);

/*			set and get, useful pour ecrire du code limpide 	*/
void	set_bool(t_mutex *mutex, bool *dest, bool value);
bool	get_bool(t_mutex *mutex, bool *value);
long	get_long(t_mutex *mutex, long *value);
void	set_long(t_mutex *mutex, long *dest, long value);
bool	simulation_finish(t_table *table);

/*			un philo tout seul trop triste 						*/
void	*alone_philo(void *arg);

/*			synchronisations									*/
void	wait_all_thread(t_table *table);
bool	all_thread_running(t_mutex *mutex, long *threads, long philo_nbr);
void	increase_long(t_mutex *mutex, long *value);

/*			utils for simulations 								*/
long	getime(t_time_code time_code);
void	precise_usleep(long usec, t_table *table);
void	clean_up(t_table *table);

/*			special write fonction 								*/
void	write_status(t_philo_status status, t_philospher *philo);

/*			Utils write wrap fonction							*/
void	ft_w_thinking(t_philo_status status, t_philospher *philo, long ecouler);
void	ft_w_sleeping(t_philo_status status, t_philospher *philo, long ecouler);
void	ft_w_eating(t_philo_status status, t_philospher *philo, long ecouler);
void	ft1_fork(t_philo_status status, t_philospher *philo, long ecouler);
void	ft2_fork(t_philo_status status, t_philospher *philo, long ecouler);

#endif