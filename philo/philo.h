/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imannouc <imannouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:30:14 by imannouc          #+#    #+#             */
/*   Updated: 2021/11/17 19:31:52 by imannouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t			philo;
	int					philo_id;
	int					times_ate;
	long int			last_time_ate;
	long int			start;
	struct s_options	*op;
}	t_philo;

typedef struct s_options
{
	int					n_philo;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					n_times_eat;
	long int			zero_time;
	int					death;
	int					everyone_ate;
	pthread_mutex_t		log;
	pthread_mutex_t		wait;
	t_philo				*philo;
	pthread_mutex_t		*fork;
}	t_options;

int			ft_atoi(const char *str);

int			store_options(int ac, char **av, t_options *arguments);

int			start_simulation(t_options options);
void		*routine(void *data);

long int	current_time(void);
void		print(t_philo *p, char *s);

int			take_forks(t_philo *philo);

int			eat_sleep_think(t_philo *philo);

#endif