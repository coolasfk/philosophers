/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:51:54 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/19 14:40:31 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo *philos;
	philos = NULL;
	int i;
	i = 0;
	if (initial_check(argc, argv))
		return (1);
	philos = philo_init(argv);
	// set_time(argv);
	if (!philos)
		manage_error("failed to intialize philosophers\n");

	t_philo *current = philos;
	while (i < ft_atoi(argv[1]))
	{
		pthread_join(current->thread, NULL);
		current = current->next;
		i++;
        printf("chck loop main 34\n");
	}

	// clean-up babe

	return (0);
}