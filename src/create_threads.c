/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:45:38 by laugarci          #+#    #+#             */
/*   Updated: 2023/10/02 18:26:21 by laugarci         ###   ########.fr       */
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

int	print_time(t_philo *philo, char *ms)
{
	long time;

	pthread_mutex_lock(&philo->info->print);
	time = get_time() - philo->info->start_time;
	printf(WHITE_T"[%ld ms]     %d %s", time, philo->philo_id, ms);
	pthread_mutex_unlock(&philo->info->print);
	return (0);
}

int	start_sleep(t_philo *philo)
{
	long time;

	time = get_time() - philo->info->start_time;
	philo->dead = check_dead(philo);
	if (philo->dead)
			return(1);
	print_time(philo, BLUE_T"is sleeping\n");
	usleep(philo->info->time_to_sleep);
	return(0);
}

int	start_think(t_philo *philo)
{
	long time;

	time = get_time() - philo->info->start_time;
	philo->dead = check_dead(philo);
	if (philo->dead)
		return(1);
	print_time(philo, YELLOW_T"is thinking\n");
	return (0);
}

int	start_eat(t_philo *philo)
{
	long time;

	time = get_time() - philo->info->start_time;
	philo->dead = check_dead(philo);
	if (philo->dead)
			return(1);	
	if (philo->philo_id % 2 == 0)
		usleep(philo->info->time_to_eat);
	pthread_mutex_lock(&philo->info->forks[philo->philo_id - 1]);
	print_time(philo, GREEN_T"has taken right fork\n");
	if (philo->philo_id == philo->info->num_philo)
		pthread_mutex_lock(&philo->info->forks[0]);
	else
		pthread_mutex_lock(&philo->info->forks[philo->philo_id]);
	philo->dead = check_dead(philo);
	print_time(philo, GREEN_T"has taken left fork\n");
	philo->dead = check_dead(philo);
	print_time(philo, GREEN_T"is eating\n");
	philo->meals_eaten++;
	usleep(philo->info->time_to_eat);
	pthread_mutex_unlock(&philo->info->forks[philo->philo_id - 1]);
	if (philo->philo_id == philo->info->num_philo)
		pthread_mutex_unlock(&philo->info->forks[0]);
	else
		pthread_mutex_unlock(&philo->info->forks[philo->philo_id]);
	philo->dead = check_dead(philo);
	if (philo->dead)
			return(1);
	return (0);
}

int	philo_die(t_philo *philo)
{
	print_time(philo, RED_T"died\n");
	return (0);
}

void	destroy_all_mutex(t_philo *philo)
{
	int	i;
	
	i = 0;
	while (i < philo->info->num_philo)
	{
		pthread_detach(philo[i].threads);
		i++;
	}
	pthread_mutex_destroy(&philo->info->print);
}

int	check_dead(t_philo *philo)
{
	long time;

	time = get_time() - philo->info->start_time;
	if (time >= philo->info->time_to_die)
		return (1);
	return (0);
}

void *start_routine(void *ph)
{
    t_philo *philo;
	long  time;
	int	first_dead;

    philo = (t_philo *)ph;
    philo->info->start_time = get_time();
	philo->dead = 0;
	first_dead = 1;
    while (42)
    {
		time = get_time() - philo->info->start_time;
		philo->dead = check_dead(philo);
		if (philo->dead)
		{
			if (first_dead)
			{
				philo_die(philo);
				first_dead = 0;
			}
			pthread_exit(NULL);
			break ;
		}
		philo->dead = start_eat(philo);
		if (philo->dead)
		{
			if (first_dead)
			{
				philo_die(philo);
				first_dead = 0;
			}
			pthread_exit(NULL);
			break ;
		}
		philo->dead = start_think(philo);
		if (philo->dead)
		{
			if (first_dead)
			{
				philo_die(philo);
				first_dead = 0;
			}
			pthread_exit(NULL);
			break ;
		}
		philo->dead = start_sleep(philo);
		if (philo->dead)
		{
			if (first_dead)
			{
				philo_die(philo);
				first_dead = 0;
			}
			pthread_exit(NULL);
			break ;
		}
		if (philo->meals_eaten == philo->info->num_times_must_eat)
			pthread_exit(NULL);
	}
	if (philo->dead)
	{
		if (first_dead)
			philo_die(philo);
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
	destroy_all_mutex(philo);
	while (i < info->num_philo)
	{
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
//	free(philo);
	return (0);
}

