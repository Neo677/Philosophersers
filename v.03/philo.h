//      header

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

typedef pthread_mutex_t t_mutex;

// IOU pour le compilateur
//typedef struct s_table t_table;

// ANSI sequence pour output avec de jolie couleur
/*Usage: 
    printf(R "this is red text.", RST);
    printf(B "this is blue text.", RST);

    Ne pas oublier de RST (reset) la couleur apres affichage
*/

#define RST "\33[0m"        //Reset couleur par defaut
#define RED "\33[1;31m"        //   Red
#define G "\33[1;32m"        //     Green
#define Y "\33[1;33m"        //        Yellow
#define B "\33[1;34m"        //        Blue
#define M "\33[1;35m"        //        Magenta
#define C "\33[1;36m"        //        Cyan
#define W "\33[1;37m"        //        White

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

typedef struct s_fork
{
    t_mutex fork;
    int fork_id;
}               t_fork;
//          structure

typedef struct s_philospher
{
    int id;
    long meals_cnt;
    bool full;
    long last_meal_time; // temps passer depuis le dernier repas ⏱️
    t_fork *left_fork;
    t_fork *righ_fork;
    pthread_t thread_id; // un philo est un thread
    t_table *table;
}               t_philospher;

// table
//     ./philo 5 800 200 200 [5]
typedef struct s_table
{
    long philo_nbr; // ./philo '5'
    long    time_to_die; // ./philo 5 800 
    long    time_to_eat; // ./philo 5 800 200 
    long    time_to_sleep; // ./philo 5 800 200 200
    long    nbr_limit_meal; // [5] |flag if -1
    long    start_simulation; // ⏱️
    bool    end_simaltions; // un philo meurt 💀 ou que tout les philo sont full 🍝
    t_fork *fork;
    t_philospher *philos;
}               t_table;

void    error_exit(const char *error);
void parse_input(t_table *table, char **av);

//          safe fonction
void *safe_malloc(size_t bytes);
void    safe_mutex(t_mutex *mutex, t_opcode opcode);
void    safe_thread_handle(t_mutex *thread, void *(*foo)(void *), void *data, t_opcode opcode);


#endif