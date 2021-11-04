/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imannouc <imannouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:43:03 by imannouc          #+#    #+#             */
/*   Updated: 2021/11/04 12:27:00 by imannouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		take_forks(t_philo *philo)
{
	int id;

	id = philo->philo_id;
	//add priority function depending on last time ate
	//to prioritize the most starving philo and avoid dying.
	// if ((philo->op->fork[id - 1].status == 0)
	// 	&& (philo->op->fork[id % (philo->op->n_philo)].status == 0))
	// {
		pthread_mutex_lock(&(philo->op->fork[id - 1].fork));
		print(philo,"has taken a fork");
		pthread_mutex_lock(&(philo->op->fork[id % (philo->op->n_philo)].fork));
		print(philo,"has taken a fork");
		// philo->op->fork[id - 1].status = 1;
		// philo->op->fork[id % philo->op->n_philo].status = 1;
		eat(philo);
	// }
	return (0);
}

int		eat(t_philo *philo)
{
	long int t1,t2;
	int id;

	id = philo->philo_id;
	t1 = current_time();
	t2 = t1;
	philo->last_time_ate = t1;
	print(philo,"is eating");
	philo->times_ate++;
	if (philo->times_ate == philo->op->n_times_eat || philo->op->n_times_eat == 0)
		exit(1);
	while ((t2 - t1) < philo->op->t_eat)
	{
		t2 = current_time();
		// if (t2 - t1 >= philo->op->t_die)
		// 	die(philo);
	}
	// philo->op->fork[id - 1].status = 0;
	pthread_mutex_unlock(&(philo->op->fork[id - 1].fork));
	// philo->op->fork[id % philo->op->n_philo].status = 0;
	pthread_mutex_unlock(&(philo->op->fork[id % (philo->op->n_philo)].fork));
	go_sleep(philo);
	return (1);
}

int		think(t_philo *philo)
{
	print(philo,"is thinking");
	return (0);
}

int		go_sleep(t_philo *philo)
{
	long int t1,t2;

	t1 = current_time();
	t2 = t1;
	print(philo,"is sleeping");
	while ((t1 - t2) < philo->op->t_sleep)
		t1 = current_time();
	think(philo);
	return (0);
}

int		die(t_philo *philo)
{
	print(philo,"died");
	exit(1);
}

void	print(t_philo *p,char *s)
{
	unsigned long int t;
	t = current_time() - p->op->zero_time;
	pthread_mutex_lock(&(p->op->log));
	printf("%ld ms %d %s\n",t,p->philo_id,s);
	pthread_mutex_unlock(&(p->op->log));
}

void	*check_death(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	while (1)
	{
		if ((current_time() - philo->last_time_ate) >= philo->op->t_die)
		{
			print(philo,"Died");
			exit(1);
		}
		// usleep(philo->op->t_eat + philo->op->t_sleep);
	}
	return (NULL);
}

// int		die() .. destroy mutexes, .. ,exit

void	*routine(void *data)
{
	t_philo *p;
	pthread_t death;

	p = (t_philo *)data;
	p->last_time_ate = current_time();
	pthread_create(&death,NULL,&check_death,p);
	pthread_detach(death);
	while (1)
	{
		take_forks(p);
	}
	return (NULL);
}
