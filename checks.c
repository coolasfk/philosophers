/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:57:51 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/19 10:53:45 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initial_check(int argc, char *argv[])
{
	int return_value = 0;
	if (argc < 5 || argc > 6)
	return_value = manage_error("wrong number of aguments");
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
	return_value = manage_error("wrong number of philosophers");
	return (return_value);
}