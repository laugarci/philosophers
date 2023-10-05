/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:41:07 by laugarci          #+#    #+#             */
/*   Updated: 2023/10/05 18:13:21 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo)
{
	long	time;
	int		eat;

	pthread_mutex_lock(&philo->info->check_dead);
	if (philo->info->num_times_must_eat > 0)
		eat = philo->info->num_philo * philo->info->num_times_must_eat;
	else
		eat = 1;
	time = get_time() - philo->info->start_time;
	if (philo->info->dead || philo->info->meals >= eat
		|| (time - philo->last_meal) >= philo->info->time_to_die
		|| philo->info->is_print)
	{
		philo->info->dead_time = get_time() - philo->info->start_time;
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
	if (check_dead(philo))
	{
		philo->info->dead = 1;
		pthread_mutex_unlock(&philo->info->print);
		return (1);
	}
	time = get_time() - philo->info->start_time;
	printf(WHITE_T"[%ld ms]     %d %s", time, philo->philo_id, ms);
	if (check_dead(philo))
		philo->info->dead = 1;
	pthread_mutex_unlock(&philo->info->print);
	return (0);
}

int	start_sleep(t_philo *philo)
{
	int i;
	if (check_dead(philo))
		return (1);
	print_time(philo, LBLUE_T"is sleeping\n");
	i = 0;
	while (i < 6)
	{
		usleep(philo->info->time_to_sleep / 6 * 1000);
		if (check_dead(philo))
			return(1);
		i++;
	}
	return (0);
}

int	start_think(t_philo *philo)
{
	print_time(philo, LCYAN_T"is thinking\n");
	if (check_dead(philo))
		philo->info->dead = 1;
	return (0);
}

int	start_eat(t_philo *philo)
{
	int i;

	if (philo->philo_id % 2 == 0)
		usleep(50);
	if (check_dead(philo))
		return (1);
	take_forks(philo);
	if (check_dead(philo))
	{
		drop_forks(philo);
		return (1);
	}
	print_time(philo, GREEN_T"is eating\n");
	philo->info->meals++;
	philo->last_meal = get_time() - philo->info->start_time;
	if (check_dead(philo))
	{
		drop_forks(philo);
		return (1);
	}
	i = 0;
	while(i < 6)
	{
		usleep(philo->info->time_to_eat / 6 * 1000);
		if (check_dead(philo))
		{
			drop_forks(philo);
			return (1);
		}
		i++;
	}
	if (check_dead(philo))
	{
		drop_forks(philo);
		return (1);
	}
	drop_forks(philo);
	return (0);
}
