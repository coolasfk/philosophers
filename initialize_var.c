/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:57:42 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/19 11:31:17 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_time	*set_time(char *argv[])
{
	static t_time	*time;

	if (time)
		return (time);
	time->time_to_die = ft_atoi(argv[2]);
    time->time_to_eat = ft_atoi(argv[3]);
    time->time_to_sleep = ft_atoi(argv[4]);
    time->times_needs_eat = ft_atoi(argv[5]);
    time->program_started = 
	return (time);
}

t_time	*get_time(void)
{
	static t_time		*time;

	if (!time)
		time = set_time(NULL);
	return (time);
}
