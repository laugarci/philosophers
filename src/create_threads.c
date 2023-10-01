/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:45:38 by laugarci          #+#    #+#             */
/*   Updated: 2023/10/01 17:40:54 by laugarci         ###   ########.fr       */
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
    while (i < info->num_philo)
    {
	    philo[i].left_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	    philo[i].right_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	    pthread_mutex_init(philo[i].left_fork, NULL);
	    pthread_mutex_init(philo[i].right_fork, NULL);
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
	printf(VERDE_T"%d %s\n", philo->philo_id, "has taken left fork");
	printf(VERDE_T"%d %s\n", philo->philo_id, "has taken right fork");
	printf(VERDE_T"%d %s\n", philo->philo_id, "is eating");
	usleep(10000);
}

void	start_sleep(t_philo *philo)
{
	printf(AZUL_T"%d %s\n", philo->philo_id, "is sleeping");
	usleep(10000);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_unlock(&philo->forks);
}

void	bring_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void *start_routine(void *ph)
{
    t_philo *philo;

    philo = (t_philo *)ph;
    int i = 0;
    while (42)
    {
        start_think(philo);
	take_forks(philo);
	    pthread_mutex_lock(philo->left_fork); 
		pthread_mutex_lock(philo->right_fork); 
		start_eat(philo);
        pthread_mutex_unlock(philo->left_fork); 
		pthread_mutex_unlock(philo->right_fork); 
        start_sleep(philo);
	i++;
	if (i == 5)
		break;
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
		pthread_mutex_destroy(philo[i].left_fork);
		pthread_mutex_destroy(philo[i].right_fork);
		free(philo[i].left_fork);
		free(philo[i].right_fork);
		i++;
	}
	free(philo);
	return 0;
}
