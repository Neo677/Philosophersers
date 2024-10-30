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

// the main is a TL;DR of the program

// input = ./philo 5 800 200 200 [5]

int main(int ac, char **av)
{
    t_table table;

    if (ac == 5 || ac == 6)
    {   
        // correct input
        // 1) Error checking, filling table table
        parse_input(&table);  // done 
        // 2) Creating the actual think
        data_init(&table); // done
        // 3) 
        dinner_start(&table); // todo
        // 4) No leaks -> philo full || 1 philo die 💀
        clean_up(&table); // todo
    }
    else
    {
        // wrong input
        error_exit("Wrong input \n" G "Correct is ./philo * *** *** *** [*]"RST);
    }
}
