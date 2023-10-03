/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:45:38 by laugarci          #+#    #+#             */
/*   Updated: 2023/10/03 20:39:50 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int create_all_mutex(t_info *info)
{
    int i;

    i = 0;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_philo);
    while (i < info->num_philo)
    {
		pthread_mutex_init(&info->forks[i], NULL);
	    i++;
    }
	pthread_mutex_init(&info->meal_mutex, NULL);
	pthread_mutex_init(&info->print, NULL);
	pthread_mutex_init(&info->print_dead, NULL);
    return (0);
}

int	print_time(t_philo *philo, char *ms)
{
	long time;
	
	time = get_time() - philo->info->start_time;
	if (philo->info->dead || time >= philo->info->time_to_die || philo->info->is_print || philo->meals_eaten == philo->info->num_times_must_eat)
		return (1);
	pthread_mutex_lock(&philo->info->print);
	time = get_time() - philo->info->start_time;
	if (philo->info->dead || time >= philo->info->time_to_die || philo->info->is_print || philo->meals_eaten == philo->info->num_times_must_eat)
	{
		pthread_mutex_unlock(&philo->info->print);
		return (1);
	}
	printf(WHITE_T"[%ld ms]     %d %s", time, philo->philo_id, ms);
	pthread_mutex_unlock(&philo->info->print);
	return (0);
}

int	start_sleep(t_philo *philo)
{
	int check;
	long	time;

	check = print_time(philo, BLUE_T"is sleeping\n");
	if (check)
		return (check);
	usleep(philo->info->time_to_sleep);
	time = get_time() - philo->info->start_time;
	if (philo->info->dead || time >= philo->info->time_to_die || philo->info->is_print || philo->meals_eaten == philo->info->num_times_must_eat)
		return (1);
	return(check);
}

int	start_think(t_philo *philo)
{
	int check;
	long	time;

	check = print_time(philo, YELLOW_T"is thinking\n");
	if (check)
		return (check);
	time = get_time() - philo->info->start_time;
	if (philo->info->dead || time >= philo->info->time_to_die || philo->info->is_print || philo->meals_eaten == philo->info->num_times_must_eat)
		return (1);
	return (check);
}

int	start_eat(t_philo *philo)
{
	int check;
	long	time;

	if (philo->philo_id % 2 == 0)
		usleep(philo->info->time_to_eat * 100);
	pthread_mutex_lock(&philo->info->forks[philo->philo_id - 1]);
	time = get_time() - philo->info->start_time;
	if (philo->info->dead || time >= philo->info->time_to_die || philo->info->is_print || philo->meals_eaten == philo->info->num_times_must_eat)
	{
		pthread_mutex_unlock(&philo->info->forks[philo->philo_id - 1]);
		return (1);
	}
	check = print_time(philo, GREEN_T"has taken right fork\n");
	if (check)
	{
		pthread_mutex_unlock(&philo->info->forks[philo->philo_id - 1]);
		return (check);
	}
	if (philo->philo_id == philo->info->num_philo)
		pthread_mutex_lock(&philo->info->forks[0]);
	else
		pthread_mutex_lock(&philo->info->forks[philo->philo_id]);
	time = get_time() - philo->info->start_time;
	if (philo->info->dead || time >= philo->info->time_to_die || philo->info->is_print || philo->meals_eaten == philo->info->num_times_must_eat)
	{
		pthread_mutex_unlock(&philo->info->forks[philo->philo_id - 1]);
		if (philo->philo_id == philo->info->num_philo)
			pthread_mutex_unlock(&philo->info->forks[0]);
		else
			pthread_mutex_unlock(&philo->info->forks[philo->philo_id]);
		return (1);
	}
	check = print_time(philo, GREEN_T"has taken left fork\n");
	time = get_time() - philo->info->start_time;
	if (philo->info->dead || time >= philo->info->time_to_die || philo->info->is_print || philo->meals_eaten == philo->info->num_times_must_eat)
	{
		pthread_mutex_unlock(&philo->info->forks[philo->philo_id - 1]);
		if (philo->philo_id == philo->info->num_philo)
			pthread_mutex_unlock(&philo->info->forks[0]);
		else
			pthread_mutex_unlock(&philo->info->forks[philo->philo_id]);
		return (1);
	}
	check = print_time(philo, GREEN_T"is eating\n");
	if (check)
	{
		pthread_mutex_unlock(&philo->info->forks[philo->philo_id - 1]);
		if (philo->philo_id == philo->info->num_philo)
			pthread_mutex_unlock(&philo->info->forks[0]);
		else
			pthread_mutex_unlock(&philo->info->forks[philo->philo_id]);
		return (1);
	}
	pthread_mutex_lock(&philo->info->meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->info->meal_mutex);
	usleep(philo->info->time_to_eat);
	pthread_mutex_unlock(&philo->info->forks[philo->philo_id - 1]);
	if (philo->philo_id == philo->info->num_philo)
		pthread_mutex_unlock(&philo->info->forks[0]);
	else
		pthread_mutex_unlock(&philo->info->forks[philo->philo_id]);
	time = get_time() - philo->info->start_time;
	if (philo->info->dead || time >= philo->info->time_to_die || philo->info->is_print || philo->meals_eaten == philo->info->num_times_must_eat)
		return (1);
	return (0);
}

void	philo_die(t_philo *philo)
{
	long time;
	
	time = get_time() - philo->info->start_time;
	printf(WHITE_T"[%ld ms]      %d %s\n", time, philo->philo_id, RED_T"died");
}

void	destroy_all_mutex(t_philo *philo)
{
	int	i;
	
	i = 0;
		while (i < philo->info->num_philo)
	{
		pthread_mutex_destroy(&philo->info->forks[i]);
		i++;
	}
}

int	check_dead(t_philo *philo)
{
	long time;

	time = get_time() - philo->info->start_time;
	if (philo->info->dead
           || philo->meals_eaten == philo->info->num_times_must_eat
          || time >= philo->info->time_to_die)
		return (1);
	return (0);
}

void *start_routine(void *ph)
{
    t_philo *philo;
	long  time;

    philo = (t_philo *)ph;
    philo->info->start_time = get_time();
	time = get_time() - philo->info->start_time;
	 while (!philo->info->dead
			 && philo->meals_eaten != philo->info->num_times_must_eat
			 && time < philo->info->time_to_die)
	 {
		 time = get_time() - philo->info->start_time;
		 if (philo->info->dead
            || philo->meals_eaten == philo->info->num_times_must_eat
            || time >= philo->info->time_to_die)
		 {
			 {
        	   pthread_mutex_lock(&philo->info->print_dead);
				   if (philo->info->dead == 1)
					   philo->info->dead = 2;
			   pthread_mutex_unlock(&philo->info->print_dead);
			 }
			 break ;
		 }
        philo->info->dead = start_eat(philo);
		time = get_time() - philo->info->start_time;
        if (philo->info->dead
            || philo->meals_eaten == philo->info->num_times_must_eat
            || time >= philo->info->time_to_die)
		{
            	 {
        	   pthread_mutex_lock(&philo->info->print_dead);
				   if (philo->info->dead == 1)
					   philo->info->dead = 2;
			   pthread_mutex_unlock(&philo->info->print_dead);
				 }
			break ;
		}
        philo->info->dead = start_sleep(philo);
		time = get_time() - philo->info->start_time;
        if (philo->info->dead
            || philo->meals_eaten == philo->info->num_times_must_eat
            || time >= philo->info->time_to_die)
		{
            	 {
        	   pthread_mutex_lock(&philo->info->print_dead);
				   if (philo->info->dead == 1)
					   philo->info->dead = 2;
			   pthread_mutex_unlock(&philo->info->print_dead);
			 }
			break ;
		}
        philo->info->dead = start_think(philo);
		time = get_time() - philo->info->start_time;
		if (philo->info->dead
            || philo->meals_eaten == philo->info->num_times_must_eat
            || time >= philo->info->time_to_die)
		{
            	 {
        	   pthread_mutex_lock(&philo->info->print_dead);
				   if (philo->info->dead == 1)
					   philo->info->dead = 2;
			   pthread_mutex_unlock(&philo->info->print_dead);
			 }
			break ;
		}
		time = get_time() - philo->info->start_time;
    }
	pthread_mutex_lock(&philo->info->print_dead);
	time = get_time() - philo->info->start_time;
    if (!philo->info->is_print && philo->info->dead == 2 && time > philo->info->start_time)
	{
        philo_die(philo);
        philo->info->is_print = 1;
    }
    pthread_mutex_unlock(&philo->info->print_dead);
	return (NULL);
}

int	create_threads(t_philo *philo, t_info *info)
{
	long		i;

	philo = (t_philo*)malloc(sizeof(t_philo) * info->num_philo); //protect malloc
	create_all_mutex(info);
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
//	free(philo);
	return (0);
}

