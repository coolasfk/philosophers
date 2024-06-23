/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:27:58 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/23 17:37:56 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_time
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_needs_eat;
	long long		start;
}					t_time;

typedef struct s_array
{
	int				*array;
	pthread_mutex_t	array_lock;
}					t_array;

typedef struct s_watch
{
	int				dead;
	pthread_mutex_t	watch_lock;
}					t_watch;

typedef struct s_philo
{
	int				id;
	int				dead_philo;
	pthread_mutex_t	fork;
	pthread_mutex_t	lock;
	pthread_mutex_t	dead;
	pthread_mutex_t	watch_lock;
	pthread_mutex_t	lock_array;
	int				total_philo;
	pthread_t		thread;
	t_time			time;
	int				time_left;
	t_array			*array;
	t_watch			*watch;
	struct s_philo	*next;
	struct s_philo	*prev;
}					t_philo;

// main
int					main(int argc, char *argv[]);
// init
t_philo				*philo_init(char *argv[]);
int					build_philos_list(t_philo **philos, int i, int num_philos);
t_philo				*build_new_node(t_philo *new_philo, int i, int num_philos);
t_watch				*set_watch(void);
t_array				*set_array(char **argv);
t_array				*get_array(void);
// utils
int					ft_atoi(const char *s);
// checks
int					initial_check(int argc, char *argv[]);
// kill_and clean
void				clean_up(t_philo *philos, int num_philos);

// philo_life
void				*philo_life(void *arg);
int					eating(t_philo *philo, int *eaten);
int					sleeping(t_philo *philo);
int					locks_status(int left, int right, int lock, t_philo *philo);
int					dead(long long time, long long start_time,
						long long time_left, t_philo *philo);
// time
t_time				*set_time(char **argv, int argc);
t_time				*get_time(void);
int					ft_usleep(long long activity_time, int time_left,
						t_philo *philo);
long long			current_time(void);
int					manage_error(char *str);
// run_threads
void				run_threads(t_philo *philo, int num_philo);
#endif