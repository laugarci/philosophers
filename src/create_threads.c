/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:45:38 by laugarci          #+#    #+#             */
/*   Updated: 2023/10/02 13:18:01 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//incrementar el numero de veces que un philosofo a comido cuando come
//implementar el tiempo que tienen para hacer cada cosa
//implementar el muerto si ha pasado mas tiempo del que deberia
//check si ha pasado mas tiempo o si ya ha comido las veces que deberia
//imprimir el tiempo en ms

int create_all_mutex(t_philo *philo, t_info *info)
{
    int i;

    i = 0;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_philo);
    while (i < info->num_philo)
    {
		pthread_mutex_init(&info->forks[i], NULL);
        pthread_mutex_init(&philo[i].meal_mutex, NULL);
	    i++;
    }
	pthread_mutex_init(&info->print, NULL);
    return (0);
}

void	print_time(t_philo *philo, char *ms)
{
	long time;

	pthread_mutex_lock(&philo->info->print);
	time = get_time() - philo->info->start_time;
	printf(WHITE_T"[%ld ms]     %d %s", time, philo->philo_id, ms);
	pthread_mutex_unlock(&philo->info->print);
}

void	start_sleep(t_philo *philo)
{
	print_time(philo, BLUE_T"is sleeping\n");
	usleep(philo->info->time_to_sleep); 
}

void	start_think(t_philo *philo)
{
	print_time(philo, YELLOW_T"is thinking\n");
}

void	start_eat(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
		usleep(philo->info->time_to_eat);
	pthread_mutex_lock(&philo->info->forks[philo->philo_id - 1]); //bloqueo derecho
	print_time(philo, GREEN_T"has taken right fork\n");
	if (philo->philo_id == philo->info->num_philo)
		pthread_mutex_lock(&philo->info->forks[0]);
	else
		pthread_mutex_lock(&philo->info->forks[philo->philo_id]);
	print_time(philo, GREEN_T"has taken left fork\n");
	print_time(philo, GREEN_T"is eating\n");
	philo->meals_eaten++;
	usleep(philo->info->time_to_eat);
	pthread_mutex_unlock(&philo->info->forks[philo->philo_id - 1]);
	if (philo->philo_id == philo->info->num_philo)
		pthread_mutex_unlock(&philo->info->forks[0]);
	else
		pthread_mutex_unlock(&philo->info->forks[philo->philo_id]);
}

void	philo_die(t_philo *philo)
{
	print_time(philo, RED_T"died\n");
}

void *start_routine(void *ph)
{
    t_philo *philo;
	long  time;

    philo = (t_philo *)ph;
    philo->info->start_time = get_time();
    while (42)
    {
		time = get_time() - philo->info->start_time;
		if (time >= philo->info->time_to_die)
		{
			philo_die(philo);
			break ;
		}
		start_eat(philo);
		start_think(philo);
		start_sleep(philo);
		if (philo->meals_eaten == philo->info->num_times_must_eat)
			pthread_exit(NULL);
	}
	return (NULL);
}

int	create_threads(t_philo *philo, t_info *info)
{
	long		i;

	philo = (t_philo*)malloc(sizeof(t_philo) * info->num_philo); //protect malloc
	create_all_mutex(philo, info);
	i = 0;
	while (i < info->num_philo)
	{
		philo[i].philo_id = i + 1;
		philo[i].info = info;
		pthread_create(&philo[i].threads, NULL, start_routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < info->num_philo)
	{
		pthread_join(philo[i].threads, NULL);
		i++;
	}
	i = 0;
	while (i < info->num_philo)
	{
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
	free(philo);
	return (0);
}

