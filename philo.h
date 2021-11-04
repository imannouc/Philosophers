#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_fork
{
	pthread_mutex_t fork;
	int	status;
}	t_fork;

typedef struct s_philo
{
	pthread_t 	philo;
	int			philo_id;
	int			times_ate;
	long int	last_time_ate;
	struct s_options *op;
}	t_philo;

typedef struct s_options
{
	int 		n_philo;
	int 		t_die;
	int 		t_eat;
	int 		t_sleep;
	int 		n_times_eat;
	long int	zero_time;
	pthread_mutex_t log;
	t_philo		*philo;
	t_fork		*fork;
}	t_options;

int		ft_atoi(const char *str);

int		store_options(int ac, char **av, t_options *arguments);
void	print_options(t_options *arg);

int		start_simulation(t_options options);
void	*routine(void *data);

long int	current_time();
void	print(t_philo *p,char *s);

int		take_forks(t_philo *philo);

int		eat(t_philo *philo);
int		go_sleep(t_philo *philo);
int		think(t_philo *philo);

int		die(t_philo *philo);

#endif