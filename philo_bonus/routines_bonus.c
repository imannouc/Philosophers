/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imannouc <imannouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 19:46:23 by imannouc          #+#    #+#             */
/*   Updated: 2021/11/19 02:01:57 by imannouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo_bonus.h"

int	eat_sleep_think(t_options *arg)
{
	if (arg->n_times_eat == 0)
		return (-1);
	sem_wait(arg->sem);
	print(arg, "has taken a fork");
	sem_wait(arg->sem);
	print(arg, "has taken a fork");
	arg->last_time_ate = current_time();
	print(arg, "is eating");
	arg->n_times_eat--;
	usleep(arg->t_eat * 1000);
	sem_post(arg->sem);
	sem_post(arg->sem);
	print(arg, "is sleeping");
	usleep(arg->t_sleep * 1000);
	print(arg, "is thinking");
	return (1);
}

void	print(t_options *arg, char *s)
{
	long int	t;

	t = current_time() - arg->zero_time;
	sem_wait(arg->log);
	printf("%ld ms %d %s\n", t, arg->philo_id, s);
	sem_post(arg->log);
}

void	*check_death(void *data)
{
	t_options	*philo;

	philo = (t_options *)data;
	while (!philo->death)
	{
		if ((current_time() - philo->last_time_ate) >= philo->t_die)
		{
			philo->death = 1;
			sem_wait(philo->log);
			printf("%ld ms %d %s\n", current_time() - philo->zero_time,
				philo->philo_id, "died");
			sem_post(philo->log);
			sem_post(philo->wait);
		}
		usleep(philo->t_die * 1000);
	}
	return (NULL);
}

int		routines(t_options *arg)
{
	pthread_t	death;
	int			eat;

	eat = arg->n_times_eat;
	if (arg->zero_time == 0)
		arg->zero_time = current_time();
	arg->last_time_ate = current_time();
	pthread_create(&death, NULL, &check_death, arg);
	pthread_detach(death);
	while (!(arg->death))
	{
		if (eat_sleep_think(arg) == -1)
		{
			break;
		}
		
	}
	return (0);
}
