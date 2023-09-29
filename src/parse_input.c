/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:12:34 by laugarci          #+#    #+#             */
/*   Updated: 2023/07/10 12:18:49 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	parse_input(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		if (!(ft_isdigit(str[i][0])) && ((str[i][0] != '-') ||
					!str[i][1]))
			return (-1);
		j = 1;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j++]))
				return (-1);
		}
		if (j > 11)
			return (-1);
		i++;
	}
	return (0);
}
