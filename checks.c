/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:57:51 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/23 16:50:38 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initial_check(int argc, char *argv[])
{
	int	return_value;

	return_value = 0;
	if (argc < 5 || argc > 6)
		return_value = manage_error("wrong number of aguments");
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
		return_value = manage_error("wrong number of philosophers");
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
		return_value = manage_error("wrong value");
	if (ft_atoi(argv[1]) == 1)
	{
		printf("0 ms philo: 1 died :(\n");
		return (1);
	}
	return (return_value);
}

int	manage_error(char *str)
{
	printf("Error: %s\n", str);
	return (1);
}
