/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:51:54 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/23 15:40:20 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo	*philo;
	int		num_philos;

	philo = NULL;
	if (initial_check(argc, argv))
		return (1);
	set_time(argv, argc);
	set_array(argv);
	philo = philo_init(argv);
	if (!philo)
	{
		manage_error("failed to initialize philosophers\n");
		return (1);
	}
	num_philos = ft_atoi(argv[1]);
	run_threads(philo, num_philos);
	clean_up(philo, num_philos);
}

void	clean_up(t_philo *philo, int num_philos)
{
	t_philo	*current;
	t_philo	*next;
	int		i;

	i = 0;
	current = philo;
	while (i < num_philos)
	{
		pthread_join(current->thread, NULL);
		pthread_mutex_destroy(&current->fork);
		current = current->next;
		i++;
	}
	i = 0;
	current = philo;
	while (i > num_philos)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

t_watch	*set_watch(void)
{
	static t_watch	*watch;

	if (watch)
		return (watch);
	watch = (t_watch *)malloc(sizeof(t_watch));
	if (!watch)
		return (NULL);
	watch->dead = 0;
	pthread_mutex_init(&watch->watch_lock, NULL);
	return (watch);
}

t_array	*set_array(char **argv)
{
	static t_array	*array;
	int				i;

	if (array)
		return (array);
	i = 0;
	array = (t_array *)malloc(sizeof(t_array));
	if (!array)
		return (NULL);
	array->array = (int *)malloc(sizeof(int) * ft_atoi(argv[1]));
	if (!array->array)
		return (NULL);
	pthread_mutex_init(&array->array_lock, NULL);
	while (i < ft_atoi(argv[1]))
	{
		array->array[i] = 0;
		i++;
	}
	return (array);
}

t_array	*get_array(void)
{
	static t_array			*array;
	static pthread_mutex_t	array_mutex;

	pthread_mutex_init(&array_mutex, NULL);
	if (!array)
		array = set_array(NULL);
	pthread_mutex_unlock(&array_mutex);
	return (array);
}
