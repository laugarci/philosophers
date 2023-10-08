/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:09:16 by laugarci          #+#    #+#             */
/*   Updated: 2023/10/08 16:20:56 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(t_philo *philo)
{
	long	time;
	long	end;

	time = 0;
	if (!philo->ph_meal && philo->philo_id % 2 != 0
		&& philo->info->num_philo != philo->philo_id)
		return (0);
	else if (!philo->ph_meal && philo->philo_id % 2 == 0)
		time = philo->info->time_to_eat;
	else if (!philo->ph_meal && philo->philo_id % 2 != 0
		&& philo->philo_id == philo->info->num_philo)
		time = philo->info->time_to_eat * 2;
	else if (philo->ph_meal && philo->info->num_philo % 2 != 0)
		time = (philo->info->time_to_eat * 2) - philo->info->time_to_sleep;
	else if (philo->ph_meal && philo->info->num_philo % 2 == 0)
		time = philo->info->time_to_eat - philo->info->time_to_sleep;
	end = time_now(philo) + time;
	while (time_now(philo) < end)
	{
		if (check_dead(philo))
			return (1);
		usleep(50);
	}
	return (0);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->philo_id - 1]);
	if (print_time(philo, YELLOW_T"has taken right fork\n"))
	{
		pthread_mutex_unlock(&philo->info->forks[philo->philo_id - 1]);
		return (1);
	}
	if (philo->philo_id == philo->info->num_philo)
		pthread_mutex_lock(&philo->info->forks[0]);
	else
		pthread_mutex_lock(&philo->info->forks[philo->philo_id]);
	if (print_time(philo, YELLOW_T"has taken left fork\n"))
	{
		drop_forks(philo);
		return (1);
	}
	return (0);
}

int	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->info->forks[philo->philo_id - 1]);
	if (philo->philo_id == philo->info->num_philo)
		pthread_mutex_unlock(&philo->info->forks[0]);
	else
		pthread_mutex_unlock(&philo->info->forks[philo->philo_id]);
	if (check_dead(philo))
		return (1);
	return (0);
}
