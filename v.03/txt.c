#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#define RED "\033[31m"
#define RST "\033[0m"

typedef pthread_mutex_t t_mutex;

typedef struct s_fork {
    t_mutex fork;
    int fork_id;
} t_fork;

typedef struct s_table t_table;

typedef struct s_philosopher {
    int id;
    long meals_cnt;
    bool full;
    long last_meal_time;
    t_fork *first_fork;
    t_fork *second_fork;
    pthread_t thread_id;
    t_mutex philo_mutex;
    t_table *table;
} t_philosopher;

typedef struct s_table {
    long philo_nbr;
    t_fork *forks;
    t_philosopher *philosophers;
} t_table;

long getime(int time_code) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    if (time_code == 0) return ts.tv_sec;
    if (time_code == 1) return ts.tv_nsec / 1000000;
    return ts.tv_nsec;
}

bool simulation_finish(t_table *table) {
    // Placeholder for actual simulation finish check
    return false;
}

void precise_usleep(long usec, t_table *table) {
    long start = getime(2);
    while (getime(2) - start < usec) {
        if (simulation_finish(table)) break;
        long elapsed = getime(2) - start;
        long rem = usec - elapsed;
        if (rem > 1e3) usleep(rem / 2);
        else while (getime(2) - start < usec);
    }
}

void error_exit(const char *error) {
    printf(RED"🚨  %s  🚨\n"RST, error);
    exit(EXIT_FAILURE);
}

void assign_forks(t_philosopher *philosopher, t_fork *forks, int philo_nbr) {
    if (philosopher->id % 2 == 0) {
        philosopher->first_fork = &forks[philosopher->id];
        philosopher->second_fork = &forks[(philosopher->id + 1) % philo_nbr];
    } else {
        philosopher->first_fork = &forks[(philosopher->id + 1) % philo_nbr];
        philosopher->second_fork = &forks[philosopher->id];
    }
}

void init_philosophers(t_table *table) {
    for (int i = 0; i < table->philo_nbr; i++) {
        table->philosophers[i].id = i;
        table->philosophers[i].meals_cnt = 0;
        table->philosophers[i].full = false;
        table->philosophers[i].last_meal_time = 0;
        table->philosophers[i].table = table;
        assign_forks(&table->philosophers[i], table->forks, table->philo_nbr);
    }
}

void philosopher_routine(t_philosopher *philosopher) {
    // Introduce a slight delay for some philosophers to avoid deadlock
    if (philosopher->id % 2 == 0) precise_usleep(1000, philosopher->table);

    while (!simulation_finish(philosopher->table)) {
        // Try to pick up forks
        if (pthread_mutex_lock(&philosopher->first_fork->fork) == 0) {
            if (pthread_mutex_lock(&philosopher->second_fork->fork) == 0) {
                // Eating
                philosopher->last_meal_time = getime(2);
                precise_usleep(1000, philosopher->table); // Simulate eating
                philosopher->meals_cnt++;
                pthread_mutex_unlock(&philosopher->second_fork->fork);
            }
            pthread_mutex_unlock(&philosopher->first_fork->fork);
        }
        // Thinking
        precise_usleep(1000, philosopher->table);
    }
}

void start_simulation(t_table *table) {
    for (int i = 0; i < table->philo_nbr; i++) {
        if (pthread_create(&table->philosophers[i].thread_id, NULL, (void *(*)(void *))philosopher_routine, &table->philosophers[i]) != 0) {
            error_exit("Failed to create philosopher thread");
        }
    }
    for (int i = 0; i < table->philo_nbr; i++) {
        pthread_join(table->philosophers[i].thread_id, NULL);
    }
}

int main(int argc, char **argv) {
    if (argc != 2) error_exit("Usage: ./philo number_of_philosophers");

    int philo_nbr = atoi(argv[1]);
    t_table table;
    table.philo_nbr = philo_nbr;
    table.forks = malloc(sizeof(t_fork) * philo_nbr);
    table.philosophers = malloc(sizeof(t_philosopher) * philo_nbr);

    for (int i = 0; i < philo_nbr; i++) {
        pthread_mutex_init(&table.forks[i].fork, NULL);
        table.forks[i].fork_id = i;
    }

    init_philosophers(&table);
    start_simulation(&table);

    for (int i = 0; i < philo_nbr; i++) {
        pthread_mutex_destroy(&table.forks[i].fork);
    }

    free(table.forks);
    free(table.philosophers);

    return 0;
}