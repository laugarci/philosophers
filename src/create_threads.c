/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:45:38 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/30 19:12:07 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int create_all_mutex(t_philo *philo, t_info* info)
{
    int i;

    i = 0;
    while (i < info->num_philo)
    {
        pthread_mutex_init(&philo[i].forks, NULL);
        i++;
    }
    return (0);
}

void	start_think(t_philo *philo)
{
	printf(AMARILLO_T"%d %s\n", philo->philo_id, "is thinking");
	usleep(10000);
}

void	start_eat(t_philo *philo)
{
	printf(VERDE_T"%d %s\n", philo->philo_id, "is eating");
	usleep(10000);
}

void	start_sleep(t_philo *philo)
{
	printf(AZUL_T"%d %s\n", philo->philo_id, "is sleeping");
	usleep(10000);
}

void *start_routine(void *ph)
{
	t_philo  *philo;
	
	philo = (t_philo *)ph;
	int i = 0;

	while (42)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		start_eat(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		start_think(philo);
		start_sleep(philo);
		i++;
		if (i == 10)
			break ;
	}	
	return (NULL);
}

int	create_threads(t_philo* philo, t_info info)
{
	long		i;
	pthread_t	*threads;

	philo = (t_philo*)malloc(sizeof(t_philo) * info.num_philo); //protect malloc
	create_all_mutex(philo, &info);
	threads = (pthread_t*)malloc(sizeof(pthread_t) * info.num_philo); //protect maloc
	i = 0;
	while (i < info.num_philo)
	{
		philo[i].philo_id = i;
		philo[i].left_fork = &philo[i].forks;
		philo[i].right_fork = &philo[(i + 1) % info.num_philo].forks;
		philo[i].num_meals = 0;
		pthread_create(&threads[i], NULL, start_routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < info.num_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	
	i = 0;
	while (i < info.num_philo)
	{
		pthread_mutex_destroy(&philo[i].forks);
		i++;
	}
	free(threads);
	free(philo);
	return 0;
}
