/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:27:58 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/21 00:16:13 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum
{
	FREE,
	LOCKED,
	SLEEPING,
	EATING,
	THINKING,
	DEAD,
}					Lock;

typedef struct s_time
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_needs_eat;
	long long		start;
}					t_time;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	fork;
	int				total_philo;
	pthread_t		thread;
	t_time			time;
	int				time_left;
	struct s_philo	*next;
	struct s_philo	*prev;

}					t_philo;

/*
typedef struct s_utils
{
	t_philo			*philo;
	int				num_philo;
	t_time			time;
}					t_utils;
*/
// main
int					main(int argc, char *argv[]);
// philo_init
t_philo				*philo_init(char *argv[]);
int					build_philos_list(t_philo **philos, int i);
t_philo				*build_new_node(t_philo *new_philo, int i);
// utils
int					ft_atoi(const char *s);
// checks
int					initial_check(int argc, char *argv[]);
// kill_and clean
void clean_up(t_philo *philos, int num_philos) ;
// philo_life
void				*philo_life(void *arg);
void				eating(t_philo *philo, int *eaten, int *array_lock);
void				sleeping(t_philo *philo, int *array_lock);
int					locks_status(int *array, int left, int right, int lock);
// time
t_time				*set_time(char **argv, int argc);
t_time				*get_time(void);
int					ft_usleep(long long activity_time, int time_left);
long long			current_time(void);
// errors
int					manage_error(char *str);
// run_threads
void				run_threads(t_philo *philo, int num_philo);
#endif