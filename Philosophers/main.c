/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:07:18 by thobenel          #+#    #+#             */
/*   Updated: 2024/10/30 14:07:20 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	the main is a too long too read of the program
	input = ./philo 5 800 200 200 [5]
	1) check the input == correct input
	2) Error checking, filling table table
	3) Creating the actual think
	4) start the table
	5) nettoyer free etc... (No leaks -> philo full || 1 philo die 💀)
*/

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		parse_input(&table, argv);
		data_init(&table);
		dinner_start(&table);
		clean_up(&table);
	}
	else
		error_exit(G"Wrong input = Correct is ./philo * *** *** *** [*]"RST);
}
