/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:49:55 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/23 17:37:38 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_time	*set_time(char **argv, int argc)
{
	static t_time	*time;

	if (time)
		return (time);
	time = (t_time *)malloc(sizeof(t_time));
	if (!time)
		return (NULL);
	time->time_to_die = ft_atoi(argv[2]);
	time->time_to_eat = ft_atoi(argv[3]);
	time->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		time->times_needs_eat = ft_atoi(argv[5]);
	else
		time->times_needs_eat = 2147483647;
	time->start = current_time();
	return (time);
}

t_time	*get_time(void)
{
	static t_time	*time;

	if (!time)
		time = set_time(NULL, 0);
	return (time);
}

long long	current_time(void)
{
	long long		milliseconds;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	milliseconds = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (milliseconds);
}

int	ft_usleep(long long activity_time, int time_left, t_philo *philo)
{
	long long	end_time;
	long long	time;
	long long	start_time;

	time = current_time();
	start_time = time;
	end_time = time + activity_time;
	while (1)
	{
		if (activity_time == 947483647 && locks_status(philo->id - 1,
				philo->next->id - 1, 2, philo) == 0)
			break ;
		time = current_time();
		if (time >= end_time)
			break ;
		pthread_mutex_lock(&philo->watch->watch_lock);
		if (dead(time, start_time, (long long)time_left, philo) == -10)
			return (-10);
		pthread_mutex_unlock(&philo->watch->watch_lock);
	}
	time_left = time_left - (time - start_time);
	return (time_left);
}

int	dead(long long time, long long start_time, long long time_left,
		t_philo *philo)
{
	if (time - start_time > time_left)
	{
		printf("%lld ms philo: %d died :(\n", time - philo->time.start,
			philo->id);
		philo->watch->dead = 1;
		pthread_mutex_unlock(&philo->watch->watch_lock);
		return (-10);
	}
	else if (philo->watch->dead == 1)
	{
		pthread_mutex_unlock(&philo->watch->watch_lock);
		return (-10);
	}
	return (0);
}
