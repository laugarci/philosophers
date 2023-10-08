/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:41:07 by laugarci          #+#    #+#             */
/*   Updated: 2023/10/08 13:30:03 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo)
{
	long	time;

	time = time_now(philo);
	if (philo->info->num_times_must_eat > 0)
	{
		pthread_mutex_lock(&philo->info->t_last_meal);
		if (philo->info->meals
			>= (philo->info->num_philo * philo->info->num_times_must_eat))
		{
			pthread_mutex_unlock(&philo->info->t_last_meal);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->info->t_last_meal);
	pthread_mutex_lock(&philo->info->check_dead);
	pthread_mutex_lock(&philo->info->print);
	if (philo->info->dead
		|| (time - philo->last_meal) > philo->info->time_to_die
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

int	print_time(t_philo *philo, char *ms)
{
	long	time;

	time = time_now(philo);
	if (check_dead(philo))
		return (1);
	pthread_mutex_lock(&philo->info->print);
	printf(WHITE_T"[%ld ms]     %d %s", time, philo->philo_id, ms);
	usleep(20);
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
	int		i;
	long	time;

	ft_usleep(philo);
	if (take_forks(philo))
		return (1);
	if (print_time(philo, GREEN_T"is eating\n"))
		return (1);
	pthread_mutex_lock(&philo->info->t_last_meal);
	philo->info->meals++;
	pthread_mutex_unlock(&philo->info->t_last_meal);
	philo->last_meal = time_now(philo);
	i = 0;
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
