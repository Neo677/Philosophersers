//			header

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

// a enlever lors du push

#include <../libft/libft.h>

//          arg totaux du programme
typedef	struct s_arguments
{
    int sleep;
    int eat;
    int die;
    int total;
    int ms_eat;

    pthread_mutex_t write_mutex;
    pthread_mutex_t dead_mutex;
    pthread_mutex_t time_eat_mutex;
    pthread_mutex_t finish_mutex;

    int nb_philo_finish_eat;
    int flag_end;

    long int start_timer;
}               t_arguments;

//      setting for every philo
typedef struct s_philosopher
{
    int id;

    long int mls_eat;

    unsigned int nb_philo_eat; 

    pthread_mutex_t *right_fork;
    pthread_mutex_t left_fork;

    pthread_t   id_thread;
    pthread_t   id_thread_death;

    t_arguments *pa;

    int finish;
}               t_philosopher;

typedef    struct s_parse_struct
{
    t_philosopher *philo;
    t_arguments args;
}               t_parse_struct;

int ft_atop(const char *str);
int numeric(char **av, int i, int ac);
void    init_mutex(t_parse_struct *philo);
int initialize(t_parse_struct *phil);
int parsing_arg(int ac, char **av, t_parse_struct *phil);

#endif