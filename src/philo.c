/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:39:49 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/28 18:19:00 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philosphers(t_philo **philo, t_info *info)
{
	int		i;
	t_philo	*new;
	t_philo	*last;

	i = 1;
	while (i <= info->num_philo)
	{
		new = ft_lstnew(i);
		ft_lstadd_back(philo, new);
		i++;
	}
	if (*philo)
	{
		last = ft_lstlast(*philo);
		last->next = *philo;
	}
}

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
	return (0);
}

long get_time()
{
	struct timeval current_time;

	return (gettimeofday(&current_time, NULL));
}

int	main(int ac, char **av)
{
	t_info	info;
	t_philo	*philo;

	philo = NULL;
	if (ac != 5 && ac != 6)
		return (0);
	if (parse_input(av) == -1)
		return (1);
	start_vars(av, &info);
	create_philosphers(&philo, &info);
	info.start_time = get_time();
	printf("time >> %ld\n", info.start_time);
//	create_threads(philo, info);
}
