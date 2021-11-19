/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imannouc <imannouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:27:34 by imannouc          #+#    #+#             */
/*   Updated: 2021/11/18 23:13:07 by imannouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long int	current_time(void)
{
	struct timeval	time;
	long int		time_ms;

	gettimeofday(&time, NULL);
	time_ms = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (time_ms);
}

static void	init_args(t_options *arguments)
{
	arguments->n_philo = -1;
	arguments->t_die = -1;
	arguments->t_eat = -1;
	arguments->t_sleep = -1;
	arguments->n_times_eat = -1;
	arguments->times_ate = 0;
	arguments->eat = arguments->n_times_eat;
	arguments->death = 0;
	arguments->zero_time = 0;
	arguments->last_time_ate = 0;
}

static int	check_args(int ac, t_options *args)
{
	if (args->n_philo <= 0 || args->t_die < 60
		|| args->t_eat < 60 || args->t_sleep < 60)
		return (1);
	if ((ac == 6) && args->n_times_eat <= 0)
		return (1);
	return (0);
}

int	store_options(int ac, char **av, t_options *arguments)
{
	init_args(arguments);
	arguments->n_philo = ft_atoi(av[1]);
	arguments->t_die = ft_atoi(av[2]);
	arguments->t_eat = ft_atoi(av[3]);
	arguments->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		arguments->n_times_eat = ft_atoi(av[5]);
	if (check_args(ac, arguments))
		return (1);
	return (0);
}
