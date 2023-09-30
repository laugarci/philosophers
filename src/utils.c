/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:34:03 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/30 15:25:00 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_message(int type)
{
	if (type == 1)
		printf(AMARILLO_T"is thinking\n");
	else if (type == 2)
		printf(VERDE_T"is eating\n");
	else if (type == 3)
		printf(AZUL_T"is sleeping\n");
	else if (type == -1)
		printf(ROJO_T"is dead\n");
}
