/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imannouc <imannouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:43:03 by imannouc          #+#    #+#             */
/*   Updated: 2021/10/22 16:26:26 by imannouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	status(int id, char *status)
{
	printf("%d %s",id,status);
}

int		take_forks(t_philo *philo)
{
	int id;

	id = philo->philo_id;
	// if (philo->options->forks[id - 1].status == 0)
	// {
	// 	pthread_mutex_lock(&(philo->options->forks[id - 1].fork));
	// 	// status(id,"has taken a fork");
	// 	printf("%d %s",id,"has taken a fork");
	// 	philo->options->forks[id - 1].status = 1;
	// 	if (philo->options->forks[id % philo->options->number_of_philosophers].status == 0)
	// 	{
	// 		pthread_mutex_lock(&(philo->options->forks[(id - 1) % philo->options->number_of_philosophers].fork));
	// 		// status(id,"has taken a fork");
	// 		printf("%d %s",id,"has taken a fork");
	// 		philo->options->forks[(id - 1) % philo->options->number_of_philosophers].status = 1;
	// 	}
	// }
	return (0);
}

void	*routine(void *data)
{
	t_philo *philosopher = NULL;

	philosopher = (t_philo *)data;
	while (1)
	{
		printf("%d\n",philosopher->philo_id);
		printf("%d\n",philosopher->options->forks->status);
		// take_forks(philosopher);
		// eat();
		// sleep();
		// think();
	}
	return (NULL);
}

