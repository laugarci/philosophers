/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:45:38 by laugarci          #+#    #+#             */
/*   Updated: 2023/10/08 16:16:45 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_all_mutex(t_info *info)
{
	int	i;

	i = 0;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_philo);
	if (!info->forks)
		return (-1);
	while (i < info->num_philo)
	{
		pthread_mutex_init(&info->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&info->print, NULL);
	pthread_mutex_init(&info->t_last_meal, NULL);
	pthread_mutex_init(&info->check_dead, NULL);
	pthread_mutex_init(&info->time, NULL);
	return (0);
}

void	philo_die(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->info->print);
	time = philo->info->dead_time;
	printf(WHITE_T"[%ld ms]      %d %s\n", time, philo->philo_id, RED_T"died");
	pthread_mutex_unlock(&philo->info->print);
}

void	one_philo(t_philo *philo)
{
	long	time;

	time = time_now(philo);
	pthread_mutex_lock(&philo->info->forks[philo->philo_id - 1]);
	print_time(philo, YELLOW_T"has taken right fork\n");
	while (time_now(philo) < (time + philo->info->time_to_die))
		usleep(10);
	philo->info->dead_time = time_now(philo);
	pthread_mutex_unlock(&philo->info->forks[philo->philo_id - 1]);
	philo->info->dead = 1;
}

void	final_check(t_philo *philo)
{
	long	time;

	time = time_now(philo);
	pthread_mutex_lock(&philo->info->check_dead);
	if (!philo->info->is_print && philo->info->dead
		&& time - philo->last_meal >= philo->info->time_to_die)
	{
		philo->info->is_print = 1;
		philo_die(philo);
	}
	pthread_mutex_unlock(&philo->info->check_dead);
}

void	*start_routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	pthread_mutex_lock(&philo->info->time);
	philo->info->start_time = get_time();
	pthread_mutex_unlock(&philo->info->time);
	while (42)
	{
		if (philo->info->num_philo == 1)
		{
			one_philo(philo);
			break ;
		}
		if (start_eat(philo) == 1)
			break ;
		if (start_sleep(philo) == 1)
			break ;
		if (start_think(philo) == 1)
			break ;
	}
	final_check(philo);
	return (NULL);
}
