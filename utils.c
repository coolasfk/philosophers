/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:02:04 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/24 11:15:42 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *s)
{
	long	num;

	num = 0;
	while ((*s >= 9 && *s <= 13) || *s == ' ')
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			return (-1);
		s++;
	}
	while (*s >= 48 && *s <= 57)
	{
		num = (num * 10) + (*s - 48);
		if (num > 2147483647)
			return (-1);
		s++;
	}
	return (num);
}

int	print_info(int flag, t_philo *philo, long long time)
{
	if (flag == 5)
		return (5);
	if (flag == 0)
	{
		flag = 5;
		printf("%lld ms philo: %d starts to eat :)\n", (time
				- philo->time.start), philo->id);
	}
	else if (flag == 1)
	{
		flag = 5;
		printf("%lld Philosopher %d starts to sleep :)\n", (time
				- philo->time.start), philo->id);
	}
	else if (flag == 2)
	{
		flag = 5;
		printf("%lld ms philo: %d starts to think :)\n", (time
				- philo->time.start), philo->id);
	}
	return (flag);
}
