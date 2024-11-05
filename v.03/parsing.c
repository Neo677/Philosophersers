/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:07:23 by thobenel          #+#    #+#             */
/*   Updated: 2024/10/30 14:07:26 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

static int is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

// inline ????
// check man
static int is_space(char c)
{
    return ((c >= 9 && c <= 13 ) || c == 32);
}

/*  1) check for negative
  2) check is the number is legit 
        ex : "  +77$%" ✅   || "  +&%42" 🚨
  3) check for int max      (2132152512312512 == too big)
                            (check for len 2_324_23_435_213 | if len > 10, sure > INTM_AX !)
                            (2_324_23_435_213 -> 9_999_99_999_999) still to check 
    
    why the Fonction return a pointer ? 
        if ("       +77&%£")
                ret  ⬆️
*/
static const char *ft_valid_input(const char *str)
{
    int len;    // len fo str
    const char *nbr;

    len = 0;
    // 1) skip the space
    while (is_space(*str))
        ++str;
    if (*str == '+')
        ++str;
    else if (*str == '-')
        error_exit("Feed me only positive value u suck !");
    if (!is_digit(*str))
        error_exit("The input is not a correct digit");
    nbr = str; // "       +77&%£"
    while (is_digit(*str++))
        len++;
    if (len > 10)
        error_exit("The value is too big, INT_MAX is the limit");
    return (nbr);
}

static long ft_atol(const char *str)
{
    long nbr;

    nbr = 0; 
    str = ft_valid_input(str); 
    while(is_digit(*str))
        nbr = (nbr * 10) + (*str++ - 48);
    if (nbr > INT_MAX)
        error_exit("The value is too big, INT_MAX is the limit");
    return (nbr);
}

/*                ms   ms  ms
        ./philo 5 800 200 200 [5]
         av[1] av[2] av[3] av[4] ...
 1) des chiffre  ✅
 2) not > INT_MAX 
 3) timestamps > 60ms 
*/

void parse_input(t_table *table, char **av)
{
    table->philo_nbr = ft_atol(av[1]);
    table->time_to_die = ft_atol(av[2]) * 1e3; // 1000
    table->time_to_eat = ft_atol(av[3]) * 1e3; // 1000
    table->time_to_sleep = ft_atol(av[4]) * 1e3; // 1000

    // same = if (table->time_to_die < 60000)
    if (table->time_to_die < 6e4 || table->time_to_eat < 6e4 || table->time_to_sleep < 6e4)
    {
        error_exit("Use timestamps major than 60ms");
    }
    if (av[5])
        table->nbr_limit_meal = ft_atol(av[5]);
    else
        table->nbr_limit_meal = -1;
    printf(Y"the parsing from the input is done\n"RST);
	//printf(Y"%ld", table->)
}
