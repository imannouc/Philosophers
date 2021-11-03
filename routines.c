/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imannouc <imannouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:43:03 by imannouc          #+#    #+#             */
/*   Updated: 2021/11/03 18:23:09 by imannouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		take_forks(t_philo *philo)
{
	int id;

	id = philo->philo_id;
	if ((philo->op->fork[id - 1].status == 0)
		&& (philo->op->fork[id % (philo->op->n_philo)].status == 0))
	{
		pthread_mutex_lock(&(philo->op->fork[id - 1].fork));
		philo->op->fork[id - 1].status = 1;
		print(id,"has taken a fork",philo);
		pthread_mutex_lock(&(philo->op->fork[id % (philo->op->n_philo)].fork));
		philo->op->fork[id % philo->op->n_philo].status = 1;
		print(id,"has taken a fork",philo);
		eat(philo);
	}
	return (0);
}

int		eat(t_philo *philo)
{
	long int t1,t2;
	int id;

	id = philo->philo_id;
	t1 = current_time();
	t2 = t1;
	philo->last_time_eaten = t1;
	print(id,"is eating",philo);
	while ((t2 - t1) < philo->op->t_eat)
	{
		t2 = current_time();
		continue;
	}
	pthread_mutex_unlock(&(philo->op->fork[id - 1].fork));
	philo->op->fork[id - 1].status = 0;
	pthread_mutex_unlock(&(philo->op->fork[id % (philo->op->n_philo)].fork));
	philo->op->fork[id % philo->op->n_philo].status = 0;
	go_sleep(philo);
	return (1);
}

int		think(t_philo *philo)
{
	print(philo->philo_id,"is thinking",philo);
	return (0);
}

int		go_sleep(t_philo *philo)
{
	long int t1,t2;

	t1 = current_time();
	t2 = t1;
	print(philo->philo_id,"is sleeping",philo);
	while ((t1 - t2) < philo->op->t_sleep)
	{
		t1 = current_time();
		continue;
	}
	think(philo);
	return (0);
}

void	print(int id, char *s, t_philo *p)
{
	unsigned long int t;
	t = current_time() - p->op->zero_time;
	pthread_mutex_lock(&(p->op->log));
	printf("%ld ms %d %s\n",t,id,s);
	pthread_mutex_unlock(&(p->op->log));
}

// int		check_death(t_philo *philo)
// {
// 	// t_die = 100 , last_t_eat = 200ms;
// 	// current time = 250; last_t_eat - current_time >= t_die;
// 	if (philo->last_time_eaten == 0)
// 		return (0);
// 	while (1)
// 	{
// 		if ((current_time() - philo->last_time_eaten) < philo->op->t_die)
// 			continue;
// 		else
// 		{
// 			print(philo->philo_id,"Died",philo);
// 			exit(1);
// 		}	
// 			// die();
// 	}
// 	return (0);
// }

// int		die() .. destroy mutexes, .. ,exit

void	*routine(void *data)
{
	t_philo *p;

	p = (t_philo *)data;
	while (1)
	{
		// if (!check_death(p))
			take_forks(p);
		// else
			// die(p);
		// sleep(2);
	}
	return (NULL);
}
