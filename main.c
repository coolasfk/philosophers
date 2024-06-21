/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:51:54 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/22 00:15:13 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo	*philos;
	int		num_philos;
	int		i;
	t_philo	*current;

	philos = NULL;
	i = 0;
	if (initial_check(argc, argv))
		return (1);
	set_time(argv, argc);
	set_watch();
	printf("check main\n");
	philos = philo_init(argv);
	if (!philos)
	{
		manage_error("failed to initialize philosophers\n");
		return (1);
	}
	num_philos = ft_atoi(argv[1]);
	printf("now only initializing the threads\n");
	run_threads(philos, num_philos);
	current = philos;
	for (i = 0; i < num_philos; i++)
	{
		printf("count------------%d\n", i);
		pthread_join(current->thread, NULL);
		pthread_mutex_destroy(&current->fork);
		current = current->next;
	}
	clean_up(philos, num_philos);
	return (0);
}

void	clean_up(t_philo *philos, int num_philos)
{
	t_philo	*current;
	t_philo	*next;

	current = philos;
	for (int i = 0; i < num_philos; i++)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

t_watch	*set_watch(void)
{
	static t_watch	*watch;
	int				i;

	if (watch)
		return (watch);
	i = 0;
	watch = (t_watch *)malloc(sizeof(t_watch));
	if (!watch)
		return (NULL);
	watch->array = (int *)malloc(sizeof(int) * 4);
	if (!watch->array)
		return (NULL);
	watch->num_philo = 5;
	watch->dead = 0;
	pthread_mutex_init(&watch->watch_lock, NULL);
	while (i < watch->num_philo)
	{
		watch->array[i] = 0;
		i++;
	}
	return (watch);
}

t_watch	*get_watch(void)
{
	static t_watch	*watch;

	
	if (!watch)
		watch = set_watch();
    
	return (watch);
}
