#include "philo.h"

static void    init_args(t_options *arguments)
{
	arguments->n_philo = -1;
	arguments->t_die = -1;
	arguments->t_eat = -1;
	arguments->t_sleep = -1;
	arguments->n_times_eat = -1;
	arguments->death = 0;
	arguments->diff = 0;
	arguments->zero_time = 0;
	arguments->everyone_ate = 0;
}

static int check_args(int ac, t_options *args)
{
	if (args->n_philo < 0 || args->t_die < 0
		|| args->t_eat < 0 || args->t_sleep < 0)
		return (1);
	if ((ac == 6) && args->n_times_eat < 0)
		return (1);
	return (0);
}

void print_options(t_options *arg)
{
	printf("%d\n",arg->n_philo);
	printf("%d\n",arg->t_die);
	printf("%d\n",arg->t_eat);
	printf("%d\n",arg->t_sleep);
	printf("%d\n",arg->n_times_eat);
}

int store_options(int ac, char **av, t_options *arguments)
{
	init_args(arguments);
	arguments->n_philo = ft_atoi(av[1]);
	arguments->t_die = ft_atoi(av[2]);
	arguments->t_eat = ft_atoi(av[3]);
	arguments->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		arguments->n_times_eat = ft_atoi(av[5]);
	if (check_args(ac,arguments))
		return (1);
	return (0);
}
