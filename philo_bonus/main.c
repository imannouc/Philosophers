/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imannouc <imannouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 20:52:26 by imannouc          #+#    #+#             */
/*   Updated: 2021/11/19 02:03:17 by imannouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int		init(t_options *args)
{
	sem_unlink("wait");
	sem_unlink("log");
	sem_unlink("forks");
	args->sem = sem_open("forks", O_CREAT , 666, args->n_philo);
	args->log = sem_open("log", O_CREAT, 666, 1);
	args->wait = sem_open("wait", O_CREAT, 666, 1);
	if (args->n_times_eat != -1)
	{
		sem_unlink("eat");
		args->everyone_ate = sem_open("eat", O_CREAT, 666, args->n_philo);
	}
	return (0);
}

void	exit_free(t_options *args)
{
	sem_close(args->sem);
	sem_close(args->log);
	sem_close(args->wait);
	if (args->pid)
		free(args->pid);
}

int		start(t_options *args)
{
	int i;
	int n;

	n = 0;
	i = 0;
	init(args);
	args->pid = (int *)malloc(sizeof(int) * args->n_philo);
	sem_wait(args->wait);
	while (i < args->n_philo)
	{
		args->philo_id = i + 1;
		args->pid[i] = fork();
		if (!args->pid[i])
			routines(args);
		i++;
	}
	i = -1;
	if (args->n_times_eat != -1)
	{
		while (++i < args->n_philo)
		{
			waitpid(args->pid[i],&n,0);
		}
		sem_post(args->wait);
	}
	sem_wait(args->wait);
	while (i--)
		kill(args->pid[i],SIGINT);
	sem_post(args->wait);
	exit_free(args);
	return (0);
}

int		main(int ac, char **av)
{
	t_options args;

	if ((ac == 5 || ac == 6) && !store_options(ac, av, &args))
		start(&args);
	else
		printf("Enter correct arguments.\n");
	return (0);
}
