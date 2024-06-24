/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:50:01 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/24 13:12:21 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *arg)
{
	t_philo	*philo;
	int		eaten;

	eaten = 0;
	philo = (t_philo *)arg;
	while (eaten < philo->time.times_needs_eat)
	{
		philo->time_left = ft_usleep(947483647, philo->time_left, philo, 2);
		if (philo->time_left < 1)
			return (NULL);
		if (eating(philo, &eaten) == 1)
			return (NULL);
		if (eaten < philo->time.times_needs_eat)
		{
			if (sleeping(philo) == 1)
				return (NULL);
		}
	}
	if(philo->id == philo->total_philo && eaten == philo->time.times_needs_eat)
	print_end(2);
	return (NULL);
}

int	eating(t_philo *philo, int *eaten)
{
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->next->fork);
	locks_status(philo->id - 1, philo->next->id - 1, 1, philo);
	if (ft_usleep(philo->time.time_to_eat, philo->time_left, philo, 0) == -10)
	{
		locks_status(philo->id - 1, philo->next->id - 1, 0, philo);
		pthread_mutex_unlock(&philo->next->fork);
		pthread_mutex_unlock(&philo->fork);
		return (1);
	}
	*eaten = *eaten + 1;
	philo->time_left = philo->time.time_to_die;
	locks_status(philo->id - 1, philo->next->id - 1, 0, philo);
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_unlock(&philo->fork);
	return (0);
}

int	sleeping(t_philo *philo)
{
	philo->time_left = ft_usleep(philo->time.time_to_sleep, philo->time_left,
			philo, 1);
	if (philo->time_left == -10)
		return (1);
	return (0);
}

int	locks_status(int left, int right, int lock, t_philo *philo)
{
	pthread_mutex_lock(&philo->array->array_lock);
	if (lock == 1)
	{
		philo->array->array[left] = 1;
		philo->array->array[right] = 1;
	}
	else if (lock == 0)
	{
		philo->array->array[left] = 0;
		philo->array->array[right] = 0;
	}
	else if (lock == 2)
	{
		if (philo->array->array[left] == 1 || philo->array->array[right] == 1)
		{
			pthread_mutex_unlock(&philo->array->array_lock);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->array->array_lock);
	return (0);
}
