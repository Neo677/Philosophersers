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
 #define PHILO_H

#include <stdio.h> // printf
#include <stdlib.h> // malloc free
#include <unistd.h> // writ, usleep 👀
#include <stdbool.h>
#include <pthread.h> // mute: init destroy lock unlock
                    // threads : create join detach
#include <sys/time.h> // gettimeofday ⏱️
#include <limits.h> // int max
#include <errno.h>

// IOU pour le compilateur
//typedef struct s_table t_table;

// ANSI sequence pour output avec de jolie couleur
/*Usage: 
    printf(R "this is red text.", RST);
    printf(B "this is blue text.", RST);

    Ne pas oublier de RST (reset) la couleur apres affichage
*/

#define RST  "\33[0m"      //Reset couleur par defaut
#define RED "\33[1;31m"        //   Red
#define G "\33[1;32m"        //     Green
#define Y "\33[1;33m"        //        Yellow
#define B "\33[1;34m"        //        Blue
#define M "\33[1;35m"        //        Magenta
#define C "\33[1;36m"        //        Cyan
#define W "\33[1;37m"        //        White

// #define RST         //Reset couleur par defaut

/* write fonction macro */
#define DEBUG_MODE 0

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

/*
   OPCODE for mutex || thread fonction
*/
typedef enum e_opcode
{
    LOCK,
    UNLOCK,
    INIT,
    DESTROY,
    CREATE,
    JOIN,
    DETACH,
}           t_opcode;

/* code for get time */
typedef enum e_time
{
	SECOND,
	MILLISECONDS,
	MICROSECONDE,
}			t_time_code;

typedef pthread_mutex_t t_mutex;

typedef struct s_fork
{
    t_mutex fork;
    int fork_id;
}               t_fork;

//          structure
typedef struct s_table t_table;


typedef struct s_philospher
{
    int id;
    long meals_cnt;
    bool full;
    long last_meal_time; // temps passer depuis le dernier repas ⏱️
    // t_fork *left_fork;
    // t_fork *righ_fork;
	t_fork *first_fork; // ODD EVEN assignement
    t_fork *second_fork;
    pthread_t thread_id; // un philo est un thread
    t_mutex philo_mutex; // useful for races with the monitor
    t_table *table;
}               t_philospher;

// table
//     ./philo 5 800 200 200 [5]
typedef struct s_table
{
    long	philo_nbr; // ./philo '5'
    long    time_to_die; // ./philo 5 '800'
    long    time_to_eat; // ./philo 5 800 '200' 
    long    time_to_sleep; // ./philo 5 800 200 '200'
    long    time_to_think;
    long    nbr_limit_meal; // '[5]' |flag if -1
    long    start_simulation; // ⏱️
    bool    end_simulations; // un philo meurt 💀 ou que tout les philo sont full 🍝
	bool 	all_thread_ready; // synchro philo
	long thread_running_nbr;
	pthread_t monitor; 
	t_mutex table_mutex; // avoid race wile reading from table
	t_mutex write_mutex;
    t_fork *fork;
    t_philospher *philos;
}               t_table;

//			utils
void error_exit(const char *error);
void parse_input(t_table *table, char **av);

//          safe fonction
void *safe_malloc(size_t bytes);
void  safe_mutex_handle(t_mutex *mutex, t_opcode opcode);
void    safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);

//			init
void data_init(t_table *table);

//			synchro utils 
void	wait_all_thread(t_table *table);

// 		set and get, very useful to write DRY(limpide) code
void	set_bool(t_mutex *mutex, bool *dest, bool value);
bool	get_bool(t_mutex *mutex, bool *value);
long 	get_long(t_mutex *mutex, long *value);
void	set_long(t_mutex *mutex, long *dest, long value);

long getime(t_time_code time_code);
void	precise_usleep(long usec, t_table *table);

bool	simulation_finish(t_table *table);

void	write_status(t_philo_status status, t_philospher *philo, bool debug);

void	dinner_start(t_table *table);
void	*dinner_simulation(void *data);

void	wait_all_thread(t_table *table);

bool 	all_thread_running(t_mutex *mutex, long *threads, long philo_nbr);

void	increase_long(t_mutex *mutex, long *value);

void	*alone_philo(void *arg);


// monitor
void	*monitor_dinner(void *data);

void clean_up(t_table *table);

bool philo_died(t_philospher *philo);

bool	all_philo_full(t_table *table);


#endif