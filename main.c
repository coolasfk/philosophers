/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:51:54 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/20 23:40:45 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char *argv[])
{
    t_philo *philos = NULL;
    int num_philos;
    int i = 0;

    if (initial_check(argc, argv))
        return 1;

    set_time(argv, argc);
    printf("check main\n");

    philos = philo_init(argv);
    if (!philos) {
        manage_error("failed to initialize philosophers\n");
        return 1;
    }

    num_philos = ft_atoi(argv[1]);
    printf("now only initializing the threads\n");

    run_threads(philos, num_philos);

    t_philo *current = philos;
    for (i = 0; i < num_philos; i++) {
        printf("count------------%d\n", i);
        pthread_join(current->thread, NULL);
        pthread_mutex_destroy(&current->fork);
        current = current->next;
    }

    clean_up(philos, num_philos);

    return 0;
}

void clean_up(t_philo *philos, int num_philos) 
{
    t_philo *current = philos;
    for (int i = 0; i < num_philos; i++) {
        t_philo *next = current->next;
        free(current);
        current = next;
    }
}


/*
nt main(int argc, char *argv[])
{
t_philo *philos;
philos = NULL;
int i;
i = 0;
if (initial_check(argc, argv))
return (1);

scss
Copy code
set_time(argv, argc);
printf("check main\n");
philos = philo_init(argv);
printf("now only initializing the threads\n");
run_threads(philos, ft_atoi(argv[1]));
if (!philos)
	manage_error("failed to intialize philosophers\n");

t_philo *current = philos;
while (i <= ft_atoi(argv[1]))
{
	printf("count------------%d\n", i);
	pthread_join(current->thread, NULL);
	pthread_mutex_destroy(&current->fork);
	current = current->next;
	i++;
}
//free(philos);
//free(current->thread);

	// clean-up babe

	return (0);
} */