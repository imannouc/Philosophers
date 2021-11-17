/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imannouc <imannouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:06:56 by imannouc          #+#    #+#             */
/*   Updated: 2021/11/17 16:12:53 by imannouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	current_time()
{
	struct timeval time;
	long int time_ms;

	gettimeofday(&time, NULL);
	time_ms = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (time_ms);
}

int		start_simulation(t_options options)
{
	t_philo philo[options.n_philo];
	t_fork forks[options.n_philo];
	int i;

	i = 0;
	options.fork = forks;
	pthread_mutex_init(&(options.log),NULL);
	while (i < options.n_philo)
	{
		if (pthread_mutex_init(&forks[i].fork,NULL))
			return (1);
		forks[i].status = 1;
		philo[i].philo_id = i + 1;
		philo[i].times_ate = 0;
		philo[i].op = &options;
		i++;
	}
	i = 0;
	while (i < options.n_philo)
	{
		if (pthread_create(&philo[i].philo,NULL,&routine,&philo[i]))
			return (1);
		philo[i].start = current_time();
		usleep(100);
		i++;
	}
	i = -1;
	while (++i < options.n_philo)
		if (pthread_detach(philo[i].philo))
			return (1);
	pthread_mutex_lock(&(options.wait));
	return (0);
}

int main(int ac, char **av)
{
	t_options arguments;

	if ((ac == 5 || ac == 6) && !store_options(ac,av,&arguments))
	{
		pthread_mutex_init(&(arguments.wait),NULL);
		pthread_mutex_lock(&(arguments.wait));
		start_simulation(arguments);
		pthread_mutex_unlock(&(arguments.wait));
		pthread_mutex_destroy(&(arguments.wait));
	}
	else
		printf("Provide correct arguments.");
	return (0);
}
