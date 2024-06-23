/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_threads.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:28:56 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/23 16:47:41 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	run_threads(t_philo *philo, int num_philo)
{
	int	i;

	i = 0;
	while (num_philo > i)
	{
		if (pthread_create(&philo->thread, NULL, philo_life, philo) != 0)
		{
			manage_error("failed to create thread");
			pthread_mutex_destroy(&philo->fork);
			return ;
		}
		philo = philo->next;
		i++;
	}
}
