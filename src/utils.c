/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 09:35:21 by laugarci          #+#    #+#             */
/*   Updated: 2023/10/08 16:13:09 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_now(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->info->time);
	time = get_time() - philo->info->start_time;
	pthread_mutex_unlock(&philo->info->time);
	return (time);
}

int	check_philo_full(t_philo *philo)
{
	if (philo->info->meals
		>= (philo->info->num_philo * philo->info->num_times_must_eat))
	{
		pthread_mutex_unlock(&philo->info->t_last_meal);
		return (1);
	}
	return (0);
}

int	check_dead(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->info->t_last_meal);
	if (philo->info->num_times_must_eat > 0)
		if (check_philo_full(philo))
			return (1);
	pthread_mutex_unlock(&philo->info->t_last_meal);
	pthread_mutex_lock(&philo->info->check_dead);
	pthread_mutex_lock(&philo->info->print);
	time = time_now(philo);
	if (philo->info->dead
		|| (time - philo->last_meal) >= philo->info->time_to_die
		|| philo->info->is_print)
	{
		philo->info->dead_time = time;
		philo->info->dead = 1;
		pthread_mutex_unlock(&philo->info->check_dead);
		pthread_mutex_unlock(&philo->info->print);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->print);
	pthread_mutex_unlock(&philo->info->check_dead);
	return (0);
}
