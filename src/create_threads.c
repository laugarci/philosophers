/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:45:38 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/30 13:43:12 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*void	*print_thinking(void *thread_id)
{
	long tid = (long)thread_id;
	printf("%ld is thinking\n", tid);
	pthread_exit(NULL);
}*/

/*void	*print_eating(void *num)
{
	long id = (long)num;
	printf("%ld is eating\n", id);
	pthread_exit(NULL);
}*/

/*void	start_dinner(void *thead_id)
{
	
}*/

void	*start_routine(void *ph)
{
	t_philo *philo;

	philo = ph;
	printf(AZUL_T"%ld\n", philo->philo_id);
	return (NULL);
}

int	create_threads(t_philo *philo, t_info *info)
{
	pthread_t threads[info->num_philo];
	long		i;
	int			err;
	t_philo 	*tmp;

	tmp = philo;
	i = 1;
	while (42)
	{
		err = pthread_create(&threads[i], NULL, start_routine, philo);
		if (err  != 0)
			return (-1);
		usleep(10000);
		tmp = tmp->next;
		i++;
	}
	i = 0;
	while (i < info->num_philo)
	{
		err = pthread_join(threads[i], NULL);
		if (err != 0)
			return (-1);
		i++;
	}
	pthread_exit(NULL);
	return (0);
}
