/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 09:35:21 by laugarci          #+#    #+#             */
/*   Updated: 2023/10/08 12:58:07 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_now(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->info->time);
	time = get_time() - philo->info->start_time;
	pthread_mutex_unlock(&philo->info->time);
	return (time);
}
