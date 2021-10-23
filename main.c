/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imannouc <imannouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:06:56 by imannouc          #+#    #+#             */
/*   Updated: 2021/10/22 16:21:56 by imannouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	current_time()
{
	struct timeval time;
	long int time_ms;

	gettimeofday(&time, NULL);
	time_ms = (time.tv_sec / 1000 + time.tv_usec * 1000);
	return (time_ms);
}


	//here I will start all threads for each philosopher.
	//init mutexes.
	// set values for fork status.
	// set philo ids.
int		start_simulation(t_philo *philosopher, t_fork *forks)
{
	int i;

	i = 0;
	while (i < philosopher->options->number_of_philosophers)
	{
		forks[i].status = 0;
		if (pthread_mutex_init(&forks[i].fork,NULL) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < philosopher->options->number_of_philosophers)
	{
		philosopher[i].philo_id = i + 1;
		i++;
	}
	i = 0;
	while (i < philosopher->options->number_of_philosophers)
	{
		if (pthread_create(&philosopher[i].philo,NULL,&routine,&philosopher[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < philosopher->options->number_of_philosophers)
	{
		if (pthread_join(philosopher[i].philo,NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int main(int ac, char **av)
{
	t_options arguments;
	t_philo *philosophers = NULL;

	if ((ac == 5 || ac == 6) && !store_options(ac,av,&arguments))
	{
		arguments.forks = malloc(sizeof(t_fork) * arguments.number_of_philosophers);
		philosophers = malloc(sizeof(t_philo) * arguments.number_of_philosophers);
		philosophers->options = &arguments;
		print_options(&arguments);
		start_simulation(philosophers,arguments.forks);
	}
	else
		printf("Provide correct arguments.");
	return (0);
}
