/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noakebli <noakebli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:21:04 by noakebli          #+#    #+#             */
/*   Updated: 2025/07/15 11:41:04 by noakebli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_data
{
	int				nb_philo;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				nb_must_eat;
	int				stop;
	long long		start_time;
	bool			flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	check;
	pthread_mutex_t	flaag;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				left_fork;
	int				right_fork;
	long long		last_meal;
	pthread_t		thread;
	t_data			*data;
	pthread_mutex_t	meal_time;
}	t_philo;

/* Parser */
int			ft_atoi(const char *str);
int			check_args(int argc, char **argv);
int			init_data(t_data *data, int argc, char **argv);
int			validate_philo_count(int nb_philo);

/* Init */
int			init_mutexes(t_data *data);
int			init_philos(t_philo **philos, t_data *data);
void		assign_forks(t_philo *philos, t_data *data);

/* Time */
long long	get_time(void);
void		ft_sleep(long long time);
long long	time_diff(long long past, long long pres);

/* Actions */
void		print_action(t_data *data, int id, char *action);
int			take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		sleeping(t_philo *philo);
void		think(t_philo *philo);

/* Simulation */
int			start_simulation(t_philo *philos, t_data *data);
void		*philo_routine(void *arg);
void		*monitor(void *arg);
int			check_death(t_philo *philo, t_data *data);
int			check_meals(t_philo *philos, t_data *data);
int			is_simulation_stopped(t_data *data);

/* Utils */
void		free_all(t_philo *philos, t_data *data);

#endif
