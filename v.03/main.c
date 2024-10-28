// header

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
        data_init(&table); // todo
        // 3) 
        dinner_start(&table); // todo
        // 4) No leaks -> philo full || 1 philo die 💀
        clean_up(&table);
    }
    else
    {
        // wrong input
        error_exit("Wrong input \n" G "Correct is ./philo * *** *** *** [*]"RST);
    }
}