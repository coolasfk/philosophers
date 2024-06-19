/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:27:58 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/19 13:15:42 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum
{
	NOT_ASSIGNED,
	SLEEPING,
	EATING,
	THINKING,
	DEAD,

}					State;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	fork;
	State			current_state;
	pthread_t		thread;

	struct s_philo	*next;

}					t_philo;

typedef struct s_time
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				program_started;
}					t_time;

typedef struct s_utils
{
	t_philo			*philo;
	int				num_philo;
	t_time			time;
}					t_utils;

// main
int					main(int argc, char *argv[]);
//philo_init
t_philo	*philo_init(char *argv[]);
int	build_philos_list(t_philo **philos, int i);
t_philo	*build_new_node(t_philo *new_philo, int i);
// utils
int					ft_atoi(const char *s);
// checks
int					initial_check(int argc, char *argv[]);
// kill_and clean
// philo_life
void* philo_life(void* arg);
// time
// philo_list
// philo_life
// errors
// initialize_var
int					manage_error(char *str);
#endif