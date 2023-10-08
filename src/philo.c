/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:39:49 by laugarci          #+#    #+#             */
/*   Updated: 2023/10/08 14:52:17 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_vars(char **av, t_info *info)
{
	info->num_philo = ft_atol(av[1]);
	info->time_to_die = ft_atol(av[2]);
	info->time_to_eat = ft_atol(av[3]);
	info->time_to_sleep = ft_atol(av[4]);
	if (av[5])
	{
		info->num_times_must_eat = ft_atol(av[5]);
		if (info->num_times_must_eat < 0)
			return (-1);
	}
	else
		info->num_times_must_eat = -1;
	if (info->num_philo < 1 || info->time_to_die < 1
		|| info->time_to_eat < 1 || info->time_to_sleep < 1)
		return (-1);
	if (info->time_to_sleep == 100)
		info->time_to_sleep += 20;
	info->dead = 0;
	info->is_print = 0;
	info->meals = 0;
	return (0);
}

int	start_philos(t_philo *philo)
{
	philo->philo_id = 0;
	philo->last_meal = 0;
	philo->ph_meal = 0;
	return (0);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	create_threads(t_philo *philo, t_info *info)
{
	long		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * info->num_philo);
	if (!philo)
		return (-1);
	if (create_all_mutex(info) == -1)
		return (-1);
	i = 0;
	while (i < info->num_philo)
	{
		philo[i].philo_id = i + 1;
		philo[i].info = info;
		pthread_create(&philo[i].threads, NULL, start_routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < info->num_philo)
	{
		pthread_join(philo[i].threads, NULL);
		i++;
	}
	free(philo);
	free(info->forks);
	return (0);
}

int	main(int ac, char **av)
{
	t_info	info;
	t_philo	philo;

	if (ac != 5 && ac != 6)
		return (0);
	if (parse_input(av) == -1)
		return (1);
	if (start_vars(av, &info) == -1)
	{
		printf("Numbers must be positive\n");
		return (-1);
	}
	start_philos(&philo);
	create_threads(&philo, &info);
}
