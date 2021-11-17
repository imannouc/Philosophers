/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imannouc <imannouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:43:03 by imannouc          #+#    #+#             */
/*   Updated: 2021/11/17 16:11:19 by imannouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		eat(t_philo *philo)
{
	int id;

	id = philo->philo_id - 1;
	if (!(philo->op->death))
	{
		pthread_mutex_lock(&(philo->op->fork[id].fork));
		print(philo,"has taken a fork 1");
		pthread_mutex_lock(&(philo->op->fork[id + 1 % (philo->op->n_philo)].fork));
		print(philo,"has taken a fork 2");
		print(philo,"is eating");
		philo->last_time_ate = current_time();
		usleep(philo->op->t_eat * 1000);
		philo->times_ate++;
		if (philo->times_ate == philo->op->n_times_eat)
			philo->op->everyone_ate++;
		pthread_mutex_unlock(&(philo->op->fork[id].fork));
		pthread_mutex_unlock(&(philo->op->fork[id + 1% (philo->op->n_philo)].fork));
		go_sleep(philo);
	}
	return (1);
}

int		go_sleep(t_philo *philo)
{
	if (!(philo->op->death))
	{
		print(philo,"is sleeping");
		usleep(philo->op->t_sleep * 1000);
		think(philo);
	}
	return (0);
}

int		think(t_philo *philo)
{	
	if (!(philo->op->death))
		print(philo,"is thinking");
	return (0);
}

void	print(t_philo *p,char *s)
{
	unsigned long int t;
	t = current_time() - p->start;
	pthread_mutex_lock(&(p->op->log));
	printf("%ld ms %d %s\n",t,p->philo_id,s);
	pthread_mutex_unlock(&(p->op->log));
}

void	*check_death(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	while (!philo->op->death)
	{
		if (philo->op->everyone_ate == philo->op->n_philo)
		{
			pthread_mutex_unlock(&(philo->op->wait));
			exit(0);
		}
		if ((current_time() - philo->last_time_ate) >= philo->op->t_die)
		{
			philo->op->death = 1;
			print(philo,"Died");
			pthread_mutex_unlock(&(philo->op->wait));
		}
		usleep(philo->op->t_die * 1000);
	}
	return (NULL);
}

void	*routine(void *data)
{
	t_philo *p;
	pthread_t death;

	p = (t_philo *)data;
	if (p->op->zero_time == 0)
		p->op->zero_time = current_time();
	p->last_time_ate = current_time();
	pthread_create(&death,NULL,&check_death,p);
	pthread_detach(death);
	while (!(p->op->death))
	{
		eat(p);
	}
	return (NULL);
}
