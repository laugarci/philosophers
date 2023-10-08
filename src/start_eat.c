/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:09:16 by laugarci          #+#    #+#             */
/*   Updated: 2023/10/08 13:31:03 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
		usleep(50);
	if ((philo->info->num_philo % 3 == 0)
		&& philo->philo_id == philo->info->num_philo)
		usleep(50);
	if (philo->info->num_philo >= 100)
	{
		if (philo->philo_id % 2 == 0)
			usleep(philo->info->num_philo);
	}
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
