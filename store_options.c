#include "philo.h"

static void    init_args(t_options *arguments)
{
	arguments->number_of_philosophers = -1;
	arguments->time_to_die = -1;
	arguments->time_to_eat = -1;
	arguments->time_to_sleep = -1;
	arguments->number_of_times_to_eat = -1;
}

static int check_args(int ac, t_options *args)
{
	if (args->number_of_philosophers < 0 || args->time_to_die < 0
		|| args->time_to_eat < 0 || args->time_to_sleep < 0)
		return (1);
	if ((ac == 6) && args->number_of_times_to_eat < 0)
		return (1);
	return (0);
}

void print_options(t_options *arg)
{
	printf("%d\n",arg->number_of_philosophers);
	printf("%d\n",arg->time_to_die);
	printf("%d\n",arg->time_to_eat);
	printf("%d\n",arg->time_to_sleep);
	printf("%d\n",arg->number_of_times_to_eat);
}

int store_options(int ac, char **av, t_options *arguments)
{
	init_args(arguments);
	arguments->number_of_philosophers = ft_atoi(av[1]);
	arguments->time_to_die = ft_atoi(av[2]);
	arguments->time_to_eat = ft_atoi(av[3]);
	arguments->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		arguments->number_of_times_to_eat = ft_atoi(av[5]);
	if (check_args(ac,arguments))
		return (1);
	return (0);
}
