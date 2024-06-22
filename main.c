/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:51:54 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/22 21:59:15 by eprzybyl         ###   ########.fr       */
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
	//set_watch(argv);
	set_array(argv);
	printf("check main\n");
	philo = philo_init(argv);
	if (!philo)
	{
		manage_error("failed to initialize philosophers\n");
		return (1);
	}
	num_philos = ft_atoi(argv[1]);
	printf("now only initializing the threads\n");
	run_threads(philo, num_philos);
	printf("after running threads\n");
	clean_up(philo, num_philos);
	return (0);
}

void	clean_up(t_philo *philo, int num_philos)
{
	t_philo	*current;
	t_philo	*next;
	int		i;

	current = philo;
	for (i = 0; i < num_philos; i++)
	{
		printf("clean up check for loop, %d 50\n", philo->id);
		pthread_join(current->thread, NULL);
		pthread_mutex_destroy(&current->fork);
		current = current->next;
	}
	current = philo;
	for (int i = 0; i < num_philos; i++)
	{
		printf("clean up check seond for loop, 50\n");
		next = current->next;
		free(current);
		current = next;
	}
}

t_watch	*set_watch(int num)
{
	static t_watch	*watch;
	int				i;

	if (watch)
		return (watch);
	i = 0;
	watch = (t_watch *)malloc(sizeof(t_watch));
	if (!watch)
		return (NULL);
	watch->array = (int *)malloc(sizeof(int) * num);
	if (!watch->array)
		return (NULL);
	watch->num_philo = num;
	watch->dead = 0;
	pthread_mutex_init(&watch->watch_lock, NULL);
	pthread_mutex_init(&watch->dead_lock, NULL);
	while (i < watch->num_philo)
	{
		watch->array[i] = 0;
		i++;
	}
	return (watch);
}
/*
t_watch	*get_watch(void)
{
	
	static t_watch	*watch;

	if (!watch)
		watch = set_watch(NULL);
	return (watch);
}*/

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
	pthread_mutex_init(&array->array_lock_helper, NULL);
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
