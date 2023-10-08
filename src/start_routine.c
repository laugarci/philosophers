/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:41:07 by laugarci          #+#    #+#             */
/*   Updated: 2023/10/08 15:48:53 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_time(t_philo *philo, char *ms)
{
	long	time;

	time = time_now(philo);
	if (check_dead(philo))
		return (1);
	pthread_mutex_lock(&philo->info->print);
	printf(WHITE_T"[%ld ms]     %d %s", time, philo->philo_id, ms);
	pthread_mutex_unlock(&philo->info->print);
	return (0);
}

int	start_sleep(t_philo *philo)
{
	int		i;
	long	time;

	if (print_time(philo, LBLUE_T"is sleeping\n") == 1)
		return (1);
	i = 0;
	time = time_now(philo);
	while (time_now(philo) < (time + philo->info->time_to_sleep))
	{
		if (check_dead(philo))
			return (1);
		usleep(50);
	}
	return (0);
}

int	start_think(t_philo *philo)
{
	if (print_time(philo, LCYAN_T"is thinking\n") == 1)
		return (1);
	return (0);
}

int	start_eat(t_philo *philo)
{
	long	time;

	if (ft_usleep(philo))
		return (1);
	if (take_forks(philo))
		return (1);
	if (print_time(philo, GREEN_T"is eating\n"))
		return (1);
	pthread_mutex_lock(&philo->info->t_last_meal);
	philo->info->meals++;
	pthread_mutex_unlock(&philo->info->t_last_meal);
	philo->ph_meal++;
	philo->last_meal = time_now(philo);
	time = time_now(philo);
	while (time_now(philo) < (time + philo->info->time_to_eat))
	{
		if (check_dead(philo))
		{
			drop_forks(philo);
			return (1);
		}
		usleep(50);
	}
	return (drop_forks(philo));
}
