/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_threads.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:28:56 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/20 19:38:11 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	run_threads(t_philo *philos, int num_philo)
{
	int i = 0;

	while (num_philo > i)
	{
		philos->time.start = current_time();
		philos->total_philo = num_philo;
		if (pthread_create(&philos->thread, NULL, philo_life, philos) != 0)
		{
			manage_error("failed to create thread");
			pthread_mutex_destroy(&philos->fork);
			/// write a function which frees the resources
			return ;
		}
		philos = philos->next;
		i++;
	}
}