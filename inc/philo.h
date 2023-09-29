/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:40:50 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/29 14:55:35 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

#define ROJO_T     "\x1b[31m"
#define VERDE_T        "\x1b[32m"
#define AMARILLO_T "\x1b[33m"
#define AZUL_T     "\x1b[34m"

struct t_info {
	int		num_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_times_must_eat;
	int		num_forks;
	long	start_time;
}			t_info;

typedef struct t_philo {
	long				philo_id;
	int					eat;
	int					sleep;
	pthread_mutex_t		*forks;
	struct t_philo		*next;
}						t_philo;

int			start_vars(char **av, t_info *info);

void		create_philosophers(t_philo **philo, t_info *info);

t_philo		*ft_lstlast(t_philo *philo);

t_philo		*ft_lstnew(int id);

void		ft_lstadd_back(t_philo **philo, t_philo *new);

int			ft_atol(const char *str);

int			ft_isdigit(int c);

int			parse_input(char **str);

int			create_threads();

void		print_message(int type);

#endif
