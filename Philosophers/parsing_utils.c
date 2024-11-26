/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:14:12 by thobenel          #+#    #+#             */
/*   Updated: 2024/11/26 16:14:49 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	ft_is_valid_input(char c)
{
	return (ft_is_space(c) || (c == '+' || c == '-'));
}
