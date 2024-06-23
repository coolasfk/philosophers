/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:49:55 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/23 14:37:47 by eprzybyl         ###   ########.fr       */
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
	start_time = time ;
	end_time = time + activity_time;
	printf("1>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>philo id: %d, time left: %d\n", philo->id, time_left);
	
	while (1)
	{
		time = current_time();
		if(activity_time == 947483647 && locks_status(philo->id - 1, philo->next->id - 1, 2, philo) == 0)
		{
			printf("-----------------------------philo %dwas thinking, time left: %lld\n", philo->id, (time_left - (time - start_time)));
			break;
		}

		pthread_mutex_lock(&philo->watch->watch_lock);
		if (time - start_time > time_left)
		{
			printf("%lld ms philo: %d died-----------, time left %lld\n", time
				- philo->time.start, philo->id, (time_left - (time - start_time) ));
			philo->watch->dead = 1;
			pthread_mutex_unlock(&philo->watch->watch_lock);
			return (-10);
		}
		else if (philo->watch->dead == 1)
		{
			printf("%lld ms philo check: %d \n", time - philo->time.start,
				philo->id);
			pthread_mutex_unlock(&philo->watch->watch_lock);
			return (-10);
		}
		pthread_mutex_unlock(&philo->watch->watch_lock);
		if (time >= end_time)
			break ;
	}
	time_left = time_left - (time - start_time);
		//printf("**************philo : %d time left whats left: %lld\n", philo->id, (time_left - (time - start_time)));
		printf("2>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>philo id: %d, time left: %d\n", philo->id, time_left);
		
	return (time_left);
}
