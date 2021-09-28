/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imannouc <imannouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:06:56 by imannouc          #+#    #+#             */
/*   Updated: 2021/09/28 15:40:23 by imannouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*eat_sleep_think(void *data)
{
	t_philo *opt;

	opt = (t_philo *)data;
	printf("Here\n");
	while (1)
	{
		eat();
		// sleep();
		// think();
	}
	return (NULL);
}

int	start_simulation(t_philo *args)
{
	//init_forks(args);
	int forks[args->number_of_philosophers];
	
	for (int j = 0; j < args->number_of_philosophers; j++){
		forks[j] = 0;// all forks are free in the start of the simulation.
	}
	// init_threads(args);
	pthread_t philo[args->number_of_philosophers];

	for (int i = 0; i < args->number_of_philosophers; i++){
		pthread_create(&philo[i],NULL,&eat_sleep_think,(void *)args);
	}
	//init_mutex();
	pthread_mutex_t fork_protect[args->number_of_philosophers];
	for (int k = 0; k < args->number_of_philosophers; k++){
		pthread_mutex_init(&fork_protect[k],NULL);
	}
	// thread_join();
	for (int m = 0; m <args->number_of_philosophers; m++){
		pthread_join(philo[m],NULL);
	}
	return (0);
}

int main(int ac, char **av)
{
	t_philo arguments;

	if ((ac == 5 || ac == 6) && !store_options(ac,av,&arguments))
	{
		print_options(&arguments);
		start_simulation(&arguments);
	}
	else
		printf("Provide correct arguments.");
	return (0);
}
