/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imannouc <imannouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:06:56 by imannouc          #+#    #+#             */
/*   Updated: 2021/11/19 01:52:44 by imannouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_options *options)
{
	int	i;

	i = 0;
	pthread_mutex_init(&(options->log), NULL);
	while (i < options->n_philo)
	{
		if (pthread_mutex_init(&(options->fork[i]), NULL))
			return (1);
		options->philo[i].philo_id = i + 1;
		options->philo[i].times_ate = 0;
		options->philo[i].op = options;
		i++;
	}
	return (0);
}

int	init_threads(t_options *options)
{
	int	i;

	i = 0;
	while (i < options->n_philo)
	{
		usleep(100);
		if (pthread_create(&(options->philo[i].philo),
				NULL, &routine, &(options->philo[i])))
			return (1);
		pthread_detach(options->philo[i].philo);
		i++;
	}
	pthread_mutex_lock(&(options->wait));
	return (0);
}

void	destroy_mutexes(t_options *options)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(options->log));
	while (i < options->n_philo)
	{
		pthread_mutex_destroy(options->fork);
		i++;
	}
}

int	start_simulation(t_options options)
{
	int	i;

	i = 0;
	options.fork = (pthread_mutex_t *)malloc(options.n_philo
			* sizeof(pthread_mutex_t));
	options.philo = (t_philo *)malloc(options.n_philo * sizeof(t_philo));
	init_forks(&options);
	init_threads(&options);
	free(options.fork);
	free(options.philo);
	destroy_mutexes(&options);
	return (0);
}

int	main(int ac, char **av)
{
	t_options	arguments;

	if ((ac == 5 || ac == 6) && !store_options(ac, av, &arguments))
	{
		pthread_mutex_init(&(arguments.wait), NULL);
		pthread_mutex_lock(&(arguments.wait));
		start_simulation(arguments);
		pthread_mutex_unlock(&(arguments.wait));
		pthread_mutex_destroy(&(arguments.wait));
	}
	else
		printf("Provide correct arguments.");
	return (0);
}
