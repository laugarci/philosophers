/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:41:07 by laugarci          #+#    #+#             */
/*   Updated: 2023/10/06 12:03:57 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->info->check_dead);
	time = get_time() - philo->info->start_time;
	if (time > 10)
		time = time - (time % 10);
	if (philo->info->num_times_must_eat > 0)
	{
		if (philo->info->meals
			>= (philo->info->num_philo * philo->info->num_times_must_eat))
		{
			pthread_mutex_unlock(&philo->info->check_dead);
			return (1);
		}
	}
	if (philo->info->dead
		|| (time - philo->last_meal) > philo->info->time_to_die)
	{
		philo->info->dead_time = time;
		philo->info->dead = 1;
		pthread_mutex_unlock(&philo->info->check_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->check_dead);
	return (0);
}

int	print_time(t_philo *philo, char *ms)
{
	long	time;

	pthread_mutex_lock(&philo->info->print);
	time = get_time() - philo->info->start_time;
	if (time > 10)
		time = time - (time % 10);
	if (check_dead(philo))
	{
		pthread_mutex_unlock(&philo->info->print);
		return (1);
	}
	printf(WHITE_T"[%ld ms]     %d %s", time, philo->philo_id, ms);
	if (check_dead(philo))
	{
		pthread_mutex_unlock(&philo->info->print);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->print);
	return (0);
}

int	start_sleep(t_philo *philo)
{
	int	i;

	if (print_time(philo, LBLUE_T"is sleeping\n") == 1)
		return (1);
	i = 0;
	if ((philo->info->time_to_sleep) > (philo->info->time_to_die / 2))
	{
		while (i <= 18)
		{
			if (check_dead(philo))
				return (1);
			usleep((philo->info->time_to_sleep / 18) * 1000);
			i++;
		}
	}
	else
	{
		while (i < 2)
		{
			if (check_dead(philo))
				return (1);
			usleep((philo->info->time_to_sleep / 2) * 1000);
			i++;
		}
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
	int	i;

	if (philo->philo_id % 2 == 0)
		usleep(50);
	if (philo->info->num_philo >= 100)
	{
		if (philo->philo_id % 2 == 0)
			usleep(250);
	}
	if (check_dead(philo))
		return (1);
	take_forks(philo);
	if (print_time(philo, GREEN_T"is eating\n"))
		return (1);
	philo->info->meals++;
	philo->last_meal = get_time() - philo->info->start_time;
	i = 0;
	if (philo->info->time_to_eat > (philo->info->time_to_die / 2))
	{
		while (i <= 18)
		{
			if (check_dead(philo))
			{
				drop_forks(philo);
				return (1);
			}
			usleep((philo->info->time_to_eat / 18) * 1000);
			i++;
		}
	}
	else
		usleep(philo->info->time_to_eat * 1000);
	if (check_dead(philo))
	{
		drop_forks(philo);
		return (1);
	}
	drop_forks(philo);
	return (0);
}
