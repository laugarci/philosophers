/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:40:50 by laugarci          #+#    #+#             */
/*   Updated: 2023/10/03 19:54:59 by laugarci         ###   ########.fr       */
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

#define RED_T     "\x1b[31m"
#define GREEN_T        "\x1b[32m"
#define YELLOW_T "\x1b[33m"
#define BLUE_T     "\x1b[34m"
#define WHITE_T		"\033[0;37m"

typedef struct t_info {
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_must_eat;
	int				num_forks;
	int				dead;
	int				is_print;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	print_dead;
	pthread_mutex_t	meal_mutex;
	long			start_time;
}					t_info;

typedef struct t_philo {
	int						philo_id;
	int						meals_eaten;
	pthread_t				threads;
	struct t_info			*info;
}							t_philo;

int			start_vars(char **av, t_info *info);

int			ft_atol(const char *str);

int			ft_isdigit(int c);

int			parse_input(char **str);

int			create_threads();

void		print_message(int type);

int			create_threads(t_philo *philo, t_info *info);

int			create_all_mutex( t_info *info);

long		get_time();

int			check_dead(t_philo *philo);

void		destroy_all_mutex(t_philo *philo);

#endif
