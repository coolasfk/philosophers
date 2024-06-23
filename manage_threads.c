/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:28:56 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/23 22:46:58 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	manage_threads(t_philo *philo, int num_philo)
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
	clean_up(philo,  num_philo, -1);
}

void clean_up(t_philo *philo, int num_philo, int i)
{
    t_philo *current;
    t_philo *next;

    current = philo;
    while (++i < num_philo)
    {
        pthread_join(current->thread, NULL);
        current = current->next;
    }  
    i = -1;
    current = philo;
    while (++i < num_philo)
    {
        next = current->next;
        if (i == 0)
        {
            free(current->array->array);
            free(current->array);
            free(current->watch);
        }
        pthread_mutex_destroy(&current->fork);
        free(current);
        current = next;
    }
}