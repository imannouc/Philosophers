/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imannouc <imannouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:43:03 by imannouc          #+#    #+#             */
/*   Updated: 2021/11/17 19:35:58 by imannouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat_sleep_think(t_philo *philo)
{
	int	id;

	id = philo->philo_id - 1;
	pthread_mutex_lock(&(philo->op->fork[id]));
	print(philo, "has taken a fork");
	pthread_mutex_lock(&(philo->op->fork[id + 1 % (philo->op->n_philo)]));
	print(philo, "has taken a fork");
	philo->last_time_ate = current_time();
	print(philo, "is eating");
	usleep(philo->op->t_eat * 1000);
	pthread_mutex_unlock(&(philo->op->fork[id]));
	pthread_mutex_unlock(&(philo->op->fork[id + 1 % (philo->op->n_philo)]));
	philo->times_ate++;
	if (philo->times_ate == philo->op->n_times_eat)
		philo->op->everyone_ate++;
	print(philo, "is sleeping");
	usleep(philo->op->t_sleep * 1000);
	print(philo, "is thinking");
	return (1);
}

void	print(t_philo *p, char *s)
{
	long int	t;

	t = current_time() - p->op->zero_time;
	pthread_mutex_lock(&(p->op->log));
	printf("%ld ms %d %s\n", t, p->philo_id, s);
	pthread_mutex_unlock(&(p->op->log));
}

void	*check_death(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		if (philo->op->everyone_ate == philo->op->n_philo)
		{
			philo->op->death = 1;
			pthread_mutex_unlock(&(philo->op->wait));
			break ;
		}
		if ((current_time() - philo->last_time_ate) >= philo->op->t_die)
		{
			philo->op->death = 1;
			pthread_mutex_lock(&(philo->op->log));
			printf("%ld ms %d %s\n", current_time() - philo->op->zero_time,
				philo->philo_id, "died");
			pthread_mutex_unlock(&(philo->op->wait));
			break ;
		}
		usleep(philo->op->t_die * 1000);
	}
	return (NULL);
}

void	*routine(void *data)
{
	t_philo		*p;
	pthread_t	death;

	p = (t_philo *)data;
	if (p->op->zero_time == 0)
		p->op->zero_time = current_time();
	p->last_time_ate = current_time();
	pthread_create(&death, NULL, &check_death, p);
	pthread_detach(death);
	while (!(p->op->death))
		eat_sleep_think(p);
	return (NULL);
}
