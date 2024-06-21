/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:50:01 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/22 00:38:45 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *arg)
{
	t_philo	*philo;
	int		eaten;

	eaten = 0;
	philo = (t_philo *)arg;
	while (eaten <= philo->time.times_needs_eat)
	{
		eating(philo, &eaten);
	}
	return (NULL);
}

void	eating(t_philo *philo, int *eaten)
{
	long long	time;

	time = (long long)current_time();
	printf("--------------philo %d is asking about the lock\n", philo->id);
	if (locks_status(philo->id - 1, philo->next->id - 1, 2, philo) == 1)
	{
		printf("At: %lld Philosopher %d starts to think :)\n", (time
				- philo->time.start), philo->id);
		while (1)
		{
			if (locks_status(philo->id - 1, philo->next->id - 1, 2, philo) == 0)
				break ;
		}
	}
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->next->fork);
	locks_status(philo->id - 1, philo->next->id - 1, 1, philo);
	time = (long long)current_time();
	printf("At: %lld Philosopher %d starts to eat :)\n", (time
			- philo->time.start), philo->id);
	ft_usleep(philo->time.time_to_eat, -100, philo);
	*eaten = *eaten + 1;
	philo->time_left = philo->time.time_to_die;
	time = (long long)current_time();
	printf("At: %lld Philosopher %d finishes to eat :)\n", (time
			- philo->time.start), philo->id);
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_unlock(&philo->fork);
	locks_status(philo->id - 1, philo->next->id - 1, 0, philo);
	if (*eaten < philo->time.times_needs_eat)
	{
		sleeping(philo);
	}
}

void	sleeping(t_philo *philo)
{
	long long	time;

	time = (long long)current_time();
	printf("%lld Philosopher %d starts to sleep :)\n", (time
			- philo->time.start), philo->id);
	ft_usleep(philo->time.time_to_sleep, philo->time_left, philo);
	time = (long long)current_time();
	printf("%lld Philosopher %d finishes to sleep :)\n", (time
			- philo->time.start), philo->id);
	printf("%lld Philosopher %d starts to think :)\n", (time
			- philo->time.start), philo->id);
	while (1)
	{
		if (locks_status(philo->id - 1, philo->next->id - 1, 2, philo) == 0)
		{
			break ;
		}
	}
}

int	locks_status(int left, int right, int lock, t_philo *philo)
{
	t_watch *watch;
	pthread_mutex_lock(&philo->watch);
	watch = get_watch();
	pthread_mutex_unlock(&philo->watch);
	pthread_mutex_lock(&watch->watch_lock);
	if (lock == 1)
	{
		watch->array[left] = 1;
		watch->array[right] = 1;
	}
	else if (lock == 0)
	{
		watch->array[left] = 0;
		watch->array[right] = 0;
	}
	else if (lock == 2)
	{
		if (watch->array[left] == 1 || watch->array[right] == 1)
		{
			pthread_mutex_unlock(&watch->watch_lock);
			return (1);
		}
	}
	pthread_mutex_unlock(&watch->watch_lock);

	return (0);
}