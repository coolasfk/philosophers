/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:50:01 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/22 22:03:21 by eprzybyl         ###   ########.fr       */
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
		if (eating(philo, &eaten) == 1)
			return (NULL);
		if (eaten < philo->time.times_needs_eat)
		{
			if (sleeping(philo) == 1)
				return (NULL);
		}
	}
	if (eaten == philo->time.times_needs_eat && philo->id == philo->total_philo)
	{
		printf("yeyyeyeyeyyeyeyyes they all have eaten!!!\n");
	}
	return (NULL);
}

int	eating(t_philo *philo, int *eaten)
{
	long long	time;

	time = (long long)current_time();
	// pthread_mutex_lock(&philo->lock);
	while (locks_status(philo->id - 1, philo->next->id - 1, 2, philo) == 1)
	{
		usleep(10000);
	}
	printf("array check eating\n");
	// pthread_mutex_unlock(&philo->lock);
	time = (long long)current_time();
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->next->fork);
	locks_status(philo->id - 1, philo->next->id - 1, 1, philo);
	printf("At: %lld Philosopher %d starts to eat :)\n", (time
			- philo->time.start), philo->id);
	if (ft_usleep(philo->time.time_to_eat, -100, philo) == 1)
	{
		locks_status(philo->id - 1, philo->next->id - 1, 0, philo);
		pthread_mutex_unlock(&philo->next->fork);
		pthread_mutex_unlock(&philo->fork);
		return (1);
	}
	*eaten = *eaten + 1;
	philo->time_left = philo->time.time_to_die;
	time = (long long)current_time();
	printf("At: %lld Philosopher %d finishes to eat :)\n", (time
			- philo->time.start), philo->id);
	locks_status(philo->id - 1, philo->next->id - 1, 0, philo);
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_unlock(&philo->fork);
	return (0);
}

int	sleeping(t_philo *philo)
{
	long long	time;

	time = (long long)current_time();
	printf("%lld Philosopher %d starts to sleep :)\n", (time
			- philo->time.start), philo->id);
	if (ft_usleep(philo->time.time_to_sleep, philo->time_left, philo) == 1)
		return (1);
	time = (long long)current_time();
	printf("%lld Philosopher %d finishes to sleep :)\n", (time
			- philo->time.start), philo->id);
	printf("%lld Philosopher %d starts to think :)\n", (time
			- philo->time.start), philo->id);
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
			//printf("---------------------philo is thinking \n");
				pthread_mutex_unlock(&philo->array->array_lock);
			return (1);
		}
	}
		pthread_mutex_unlock(&philo->array->array_lock);
	printf("array check\n");
	return (0);
}
/*
int	locks_status(int left, int right, int lock, t_philo *philo)
{
	static int	*array;
	int			i;
	t_array		*array;

	pthread_mutex_lock(&philo->lock_array);
	if (lock == 1)
	{
		philo->array[left] = 1;
		philo->array[right] = 1;
	}
	else if (lock == 0)
	{
		philo->array[left] = 0;
		philo->array[right] = 0;
	}
	else if (lock == 2)
	{
		if (philo->array[left] == 1 || philo->array[right] == 1)
		{
			printf("---------------------philo is thinking \n");
			pthread_mutex_unlock(&philo->lock_array);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->lock_array);
	printf("array check\n");
	return (0);
}*/
/*
int	locks_status(int left, int right, int lock, t_philo *philo)
{
	i = 0;
	pthread_mutex_lock(&philo->lock_array);
	array = (int *)malloc(sizeof(int) * philo->total_philo);
	if (!array)
		return (-1);
	while (i < philo->total_philo)
	{
		array[i] = 0;
		i++;
	}
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
		if (array[left] == 1 || array[right] == 1)
		{
			pthread_mutex_unlock(&philo->lock_array);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->lock_array);
	printf("array check\n");
	return (0);
}*/
/*
int locks_status(int left, int right, int lock, t_philo *philo)
{
    t_array *array;

    pthread_mutex_lock(&philo->lock_array);
    array = get_array(); // Assuming get_array is thread-safe
    
    // Lock the array's mutex to safely access/modify the array
    pthread_mutex_lock(&array->array_lock);
    if (lock == 1)
    {
        printf("yesss!---------\n");
        array->array[left] = 1;
        array->array[right] = 1;
    }
    else if (lock == 0)
    {
        array->array[left] = 0;
        array->array[right] = 0;
    }
    else if (lock == 2)
    {
        if (array->array[left] == 1 || array->array[right] == 1)
        {
            pthread_mutex_unlock(&array->array_lock);
            pthread_mutex_unlock(&philo->lock_array);
            return 1;
        }
    }
    pthread_mutex_unlock(&array->array_lock);
    pthread_mutex_unlock(&philo->lock_array);
    printf("array check\n");
    return 0;
}*/
