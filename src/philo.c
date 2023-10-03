/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:39:49 by laugarci          #+#    #+#             */
/*   Updated: 2023/10/03 14:29:36 by laugarci         ###   ########.fr       */
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
		{
			write(1, "Numbers must be positive\n", 25);
			return (-1);
		}
	}
	else
		info->num_times_must_eat = -1;
	if (info->num_philo < 1 || info->time_to_die < 1
		|| info->time_to_eat < 1 || info->time_to_sleep < 1)
	{
		write(1, "Numbers must be positive\n", 25);
		return (-1);
	}
	info->num_forks = info->num_philo;
	info->dead = 0;
	info->is_print = 0;
	return (0);
}

int	start_philos(t_philo *philo)
{
	philo->philo_id = 0;
	philo->meals_eaten = 0;
	return (0);
}

long get_time()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	main(int ac, char **av)
{
	t_info	info;
	t_philo	philo;

	if (ac != 5 && ac != 6)
		return (0);
	if (parse_input(av) == -1)
		return (1);
	start_vars(av, &info);
	start_philos(&philo);
	create_threads(&philo, &info);
}
