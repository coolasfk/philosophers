/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:50:01 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/21 00:20:31 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *arg)
{
	t_philo	*philo;
	int		eaten;
	int		*array_lock;
	int		i;

	i = 0;
	eaten = 0;
	philo = (t_philo *)arg;
	array_lock = (int *)malloc(sizeof(int) * philo->total_philo);
	if (!array_lock)
		return (NULL);
	while (i < philo->total_philo)
	{
		array_lock[i] = 0;
		i++;
	}
	while (eaten <= philo->time.times_needs_eat)
	{
		eating(philo, &eaten, array_lock);
	}
	return (NULL);
}

void	eating(t_philo *philo, int *eaten, int *array_lock)
{
	long long	time;
printf("philo nr %d TRIES to eat \n", philo->id );
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->next->fork);
	locks_status(array_lock, philo->id - 1, philo->next->id - 1, 1);
	time = (long long)current_time();
	printf("At: %lld Philosopher %d starts to eat :)\n", (time
			- philo->time.start), philo->id);
	ft_usleep(philo->time.time_to_eat, -100);
	*eaten = *eaten + 1;
	philo->time_left = philo->time.time_to_die;
	time = (long long)current_time();
	printf("At: %lld Philosopher %d finishes to eat :)\n", (time
			- philo->time.start), philo->id);
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_unlock(&philo->fork);
	locks_status(array_lock, philo->id - 1, philo->next->id - 1, 0);
	if (*eaten < philo->time.times_needs_eat)
	{
		sleeping(philo, array_lock);
	}
}

void	sleeping(t_philo *philo, int *array_lock)
{
	long long	time;

	time = (long long)current_time();
	printf("%lld Philosopher %d starts to sleep :)\n", (time
			- philo->time.start), philo->id);
	printf("------------time left check %d, %d\n", philo->id, philo->time_left);
	ft_usleep(philo->time.time_to_sleep, philo->time_left);
	time = (long long)current_time();
	printf("%lld Philosopher %d finishes to sleep :)\n", (time
			- philo->time.start), philo->id);
	printf("%lld Philosopher %d starts to think :)\n", (time
			- philo->time.start), philo->id);
	while (1)
	{
		if (locks_status(array_lock, philo->id, philo->next->id, 2) == 0)
			break ;
	}
}

int	locks_status(int *array, int left, int right, int lock)
{
	if (lock == 1)
	{
		array[left] = 1;
		array[right] = 1;
	}
	else if (lock == 0)
	{
		array[left] = 0;
		array[right] = 0;
	}
	else if (lock == 2)
	{
		if (array[left] == 1 && array[right] == 1)
			return (1);
	}
	else if (lock == 666)
	{
		return (666);
	}

	return (0);
}