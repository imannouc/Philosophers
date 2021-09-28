#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_philo
{
	int 			number_of_philosophers;
	int 			time_to_die;
	int 			time_to_eat;
	int 			time_to_sleep;
	int 			number_of_times_to_eat;
	pthread_t 		*philo;
	pthread_mutex_t *fork;
}	t_philo;

int		ft_atoi(const char *str);
int		store_options(int ac, char **av, t_philo *arguments);
void	print_options(t_philo *arg);
void	*eat_sleep_think(void *data);

#endif