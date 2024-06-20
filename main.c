/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:51:54 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/20 13:08:36 by eprzybyl         ###   ########.fr       */
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
    
	set_time(argv, argc);
    printf("check main\n");
	philos = philo_init(argv);
    printf("now only initializing the threads\n");
	run_threads(philos, ft_atoi(argv[1]));
	if (!philos)
		manage_error("failed to intialize philosophers\n");

	t_philo *current = philos;
	while (i < ft_atoi(argv[1]))
	{
		pthread_join(current->thread, NULL);
		current = current->next;
		i++;
	}

	// clean-up babe

	return (0);
}