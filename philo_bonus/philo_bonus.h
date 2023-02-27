/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imannouc <imannouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:41:44 by imannouc          #+#    #+#             */
/*   Updated: 2021/11/19 05:05:02 by imannouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_options
{
	int					n_philo;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					n_times_eat;
	long int			zero_time;
	int					death;
	int					eat;
	sem_t				*everyone_ate;
	sem_t				*log;
	sem_t				*wait;
	sem_t				*sem;
	int					*pid;
	int					philo_id;
	int					times_ate;
	long int			last_time_ate;
	long int			start;
}	t_options;

int			ft_atoi(const char *str);

int			store_options(int ac, char **av, t_options *arguments);

int			start_simulation(t_options options);

long int	current_time(void);

int			routines(t_options *arg);

int			eat_sleep_think(t_options *arg);
void		print(t_options *arg, char *s);

#endif