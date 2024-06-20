/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:49:55 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/20 17:50:20 by eprzybyl         ###   ########.fr       */
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

void	ft_usleep(long long activity_time)
{
	long long end_time;
	long long time;

	time = current_time();
	end_time = time + activity_time;
	while (1)
	{
		time = current_time();
		if (time == end_time || time > end_time)
			break ;
	}
}