#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_options
{
	int 		number_of_philosophers;
	int 		time_to_die;
	int 		time_to_eat;
	int 		time_to_sleep;
	int 		number_of_times_to_eat;
	struct s_philo 	*philosophers;
	struct s_fork *forks;
	// int			last_time_eaten;
//	t_philo // should be passed to thread function struct to store philo id + additional info threads,.. t_options.
//	t_fork // struct to store mutexes and forks ids, 
//	t_options // basic input , time stuff.
}	t_options;

typedef struct s_philo
{
	pthread_t 	philo;
	t_options	*options;
	int			philo_id;
}	t_philo;

typedef struct s_fork
{
	pthread_mutex_t fork;
	int	status;
}	t_fork;

//death
int		ft_atoi(const char *str);
int		store_options(int ac, char **av, t_options *arguments);
void	print_options(t_options *arg);
void	*routine(void *data);
int		start_simulation(t_philo *philospher, t_fork *forks);
long int	current_time();
void	*routine(void *data);
void	status(int id, char *status);
int		take_forks(t_philo *philo);

#endif