/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:41:07 by laugarci          #+#    #+#             */
/*   Updated: 2023/10/05 16:10:24 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo)
{
	long	time;
//	int		eat;

	pthread_mutex_lock(&philo->info->check_dead);
//	eat = philo->info->num_philo * philo->info->num_times_must_eat;
	time = get_time() - philo->info->start_time;
	if (philo->info->dead
	|| (time - philo->last_meal) > philo->info->time_to_die
		|| philo->info->is_print)
	{
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
	int	check;

	check = print_time(philo, LBLUE_T"is sleeping\n");
	usleep(philo->info->time_to_sleep * 1000);
	if (check || check_dead(philo))
		philo->info->dead = 1;
	return (0);
}

int	start_think(t_philo *philo)
{
	int	check;

	check = print_time(philo, LCYAN_T"is thinking\n");
	if (check || check_dead(philo))
		philo->info->dead = 1;
	return (0);
}

int	start_eat(t_philo *philo)
{
	int	check;

	if (philo->philo_id % 2 == 0)
		usleep(50);
	if (check_dead(philo))
	{
		philo->info->dead = 1;
		return (1);
	}
	pthread_mutex_lock(&philo->info->forks[philo->philo_id - 1]);
	check = print_time(philo, YELLOW_T"has taken right fork\n");
	if (philo->philo_id == philo->info->num_philo)
		pthread_mutex_lock(&philo->info->forks[0]);
	else
		pthread_mutex_lock(&philo->info->forks[philo->philo_id]);
	print_time(philo, YELLOW_T"has taken left fork\n");
	print_time(philo, GREEN_T"is eating\n");
	philo->last_meal = get_time() - philo->info->start_time;
	usleep(philo->info->time_to_eat * 1000);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->info->forks[philo->philo_id - 1]);
	if (philo->philo_id == philo->info->num_philo)
		pthread_mutex_unlock(&philo->info->forks[0]);
	else
		pthread_mutex_unlock(&philo->info->forks[philo->philo_id]);
	if (check_dead(philo))
		philo->info->dead = 1;
	return (0);
}
