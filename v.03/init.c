/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:07:12 by thobenel          #+#    #+#             */
/*   Updated: 2024/10/30 14:07:15 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


/*
	EVEN ODD fork assignement
*/
void assign_forks(t_philospher *philosopher, t_fork *forks, int philo_nbr)
{
    int left_fork_index;
    int right_fork_index;

    left_fork_index = philosopher->id;
    right_fork_index = (philosopher->id + 1) % philo_nbr;

    if (philosopher->id % 2 == 0)
    {
        // Philosophe pair : prend la fourchette de gauche puis de droite
        philosopher->first_fork = &forks[left_fork_index];
        philosopher->second_fork = &forks[right_fork_index];
    }
    else
    {
        // Philosophe impair : prend la fourchette de droite puis de gauche
        philosopher->first_fork = &forks[right_fork_index];
        philosopher->second_fork = &forks[left_fork_index];
    }
}

void	release_fork(t_philospher *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);   
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	printf("Philo %d a poser ses couvert\n", philo->id);
}


void philo_init(t_table *table)
{
    int i = 0;

    printf("Début de l'initialisation des philosophes\n");
    while (i < table->philo_nbr) {
        table->philos[i].id = i;
        table->philos[i].meals_cnt = 0;
        table->philos[i].full = false;
        table->philos[i].last_meal_time = 0;
        table->philos[i].table = table;
        safe_mutex_handle(&table->philos[i].philo_mutex, INIT);

        // Assignation des fourchettes
        assign_forks(&table->philos[i], table->fork, table->philo_nbr);
        printf("Philosophe %d initialisé avec fourchettes %d et %d\n", 
               i, table->philos[i].first_fork->fork_id, table->philos[i].second_fork->fork_id);
        i++;
    }
    printf("Fin de l'initialisation des philosophes\n");
}

void data_init(t_table *table)
{
    int i;

    printf("Début de l'initialisation des données\n");
    table->end_simulations = false;
    table->all_thread_ready = false;
    table->thread_running_nbr = 0;

    // Allocation mémoire pour les philosophes
    table->philos = safe_malloc(sizeof(t_philospher) * table->philo_nbr);
    if (!table->philos) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les philosophes\n");
        exit(EXIT_FAILURE);
    }
    printf("Mémoire allouée pour %ld philosophes\n", table->philo_nbr);

    // Allocation mémoire pour les fourchettes
    table->fork = safe_malloc(sizeof(t_fork) * table->philo_nbr);
    if (!table->fork) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les fourchettes\n");
        free(table->philos);
        exit(EXIT_FAILURE);
    }
    printf("Mémoire allouée pour les fourchettes\n");

    // Initialisation des mutex
    safe_mutex_handle(&table->table_mutex, INIT);
    safe_mutex_handle(&table->write_mutex, INIT);

    i = 0;
    while (i < table->philo_nbr) {
        safe_mutex_handle(&table->fork[i].fork, INIT);
        table->fork[i].fork_id = i;
        printf("Initialisation de la fourchette %d terminée\n", i);
        i++;
    }

    printf("Fin de l'initialisation des données de la table\n");
}