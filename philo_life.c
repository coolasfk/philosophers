/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:50:01 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/19 14:45:46 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1) 
    { // add something to exit this
        printf("Philosopher %d is thinking.\n", philo->id);
        usleep(50000); 

        // pick up the left fork (own fork)
        pthread_mutex_lock(&philo->fork);
        printf("Philosopher %d picked up their fork.\n", philo->id);

        // pick up the right fork (neighbor's fork)
        if(philo->id%2==1) ///////////////////////////--<<<<< think of better mechanism
        pthread_mutex_lock(&philo->next->fork);
        printf("Philosopher %d picked up their neighbor's fork.\n", philo->id);

        // Eating
        printf("Philosopher %d is eating.\n", philo->id);
         usleep(50000);

        // release the forks
        pthread_mutex_unlock(&philo->next->fork);
        pthread_mutex_unlock(&philo->fork);
    }
      printf("philo life 43 - exiting philo_life\n");
	return (NULL);
}
