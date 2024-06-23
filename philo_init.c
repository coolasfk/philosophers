/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:50:06 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/23 22:12:17 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*philo_init(char *argv[])
{
	int		num_philos;
	t_philo	*philos;
	int		i;

	i = 1;
	philos = NULL;
	num_philos = ft_atoi(argv[1]);
	while (num_philos + 1 > i)
	{
		if (build_philos_list(&philos, i, num_philos))
			return (NULL);
		i++;
	}
	return (philos);
}

int	build_philos_list(t_philo **philos, int i, int num_philos)
{
	t_philo	*new_philo;
	t_philo	*last;

	new_philo = build_new_node(NULL, i, num_philos);
	if (new_philo == NULL)
		return (-1);
	if (*philos == NULL)
	{
		*philos = new_philo;
		new_philo->next = new_philo;
		new_philo->prev = new_philo;
	}
	else
	{
		last = (*philos)->prev;
		last->next = new_philo;
		new_philo->prev = last;
		new_philo->next = *philos;
		(*philos)->prev = new_philo;
	}
	return (0);
}

t_philo	*build_new_node(t_philo *new_philo, int i, int num_philos)
{
	t_time	*time;

	new_philo = (t_philo *)malloc(sizeof(t_philo));
	if (!new_philo)
		return (NULL);
	new_philo->id = i;
	time = get_time();
	new_philo->time = *time;
	new_philo->time.start = current_time();
	new_philo->time_left = time->time_to_die;
	pthread_mutex_init(&new_philo->fork, NULL);
	new_philo->watch = set_watch();
	new_philo->array = get_array();
	new_philo->total_philo = num_philos;
	return (new_philo);
}
