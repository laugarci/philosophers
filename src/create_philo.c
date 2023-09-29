/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 09:42:00 by laugarci          #+#    #+#             */
/*   Updated: 2023/07/24 09:42:31 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_lstlast(t_philo *philo)
{
	if (!philo)
		return (0);
	while (philo->next)
		philo = philo->next;
	return (philo);
}

t_philo	*ft_lstnew(int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (0);
	philo->philo_id = id;
	philo->next = 0;
	return (philo);
}

void	ft_lstadd_back(t_philo **philo, t_philo *new)
{
	t_philo	*last;

	if (!new)
		return ;
	if (!*philo)
	{
		*philo = new;
		new->next = NULL;
	}
	else
	{
		last = ft_lstlast(*philo);
		last->next = new;
		new->next = NULL;
	}
}
