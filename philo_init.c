/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:50:06 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/21 00:09:59 by eprzybyl         ###   ########.fr       */
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
		if (build_philos_list(&philos, i))
			return (NULL);
		i++;
		printf("chck loop 29\n");
	}
	return (philos);
}

int	build_philos_list(t_philo **philos, int i)
{
	t_philo	*new_philo;
	t_philo	*last;

	new_philo = build_new_node(NULL, i);
	if (new_philo == NULL)
	{
		return (-1);
	}
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

t_philo	*build_new_node(t_philo *new_philo, int i)
{
	new_philo = (t_philo *)malloc(sizeof(t_philo));
	if (!new_philo)
		return (NULL);
	new_philo->id = i;
    t_time *time;
    time = get_time();
	new_philo->time = *time;
    new_philo->time.start = current_time();
    new_philo->time_left = time->time_to_die;
	if (pthread_mutex_init(&new_philo->fork, NULL) != 0)
	{
		free(new_philo);
		return (NULL);
	}
    /*
	if (pthread_create(&new_philo->thread, NULL, philo_life, new_philo) != 0)
	{
		manage_error("failed to create thread");
		pthread_mutex_destroy(&new_philo->fork);
		free(new_philo);
		return (NULL);
	}*/

	return (new_philo);
}