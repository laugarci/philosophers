/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:09:16 by laugarci          #+#    #+#             */
/*   Updated: 2023/10/06 10:01:06 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->philo_id - 1]);
	print_time(philo, YELLOW_T"has taken right fork\n");
	if (check_dead(philo))
	{
		philo->info->dead = 1;
		pthread_mutex_unlock(&philo->info->forks[philo->philo_id - 1]);
		return (1);
	}
	if (philo->philo_id == philo->info->num_philo)
		pthread_mutex_lock(&philo->info->forks[0]);
	else
		pthread_mutex_lock(&philo->info->forks[philo->philo_id]);
	print_time(philo, YELLOW_T"has taken left fork\n");
	return (0);
}

int	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->info->forks[philo->philo_id - 1]);
	if (philo->philo_id == philo->info->num_philo)
		pthread_mutex_unlock(&philo->info->forks[0]);
	else
		pthread_mutex_unlock(&philo->info->forks[philo->philo_id]);
	return (0);
}
