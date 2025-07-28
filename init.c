/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noakebli <noakebli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:21:15 by noakebli          #+#    #+#             */
/*   Updated: 2025/04/28 10:21:15 by noakebli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	int		i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->write, NULL))
		return (1);
	if (pthread_mutex_init(&data->check, NULL))
		return (1);
	if (pthread_mutex_init(&data->flaag, NULL))
		return (1);
	return (0);
}

int	init_philos(t_philo **philos, t_data *data)
{
	int		i;

	*philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!(*philos))
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].last_meal = 0;
		(*philos)[i].data = data;
		if (pthread_mutex_init(&(*philos)[i].meal_time, NULL))
			return (1);
		i++;
	}
	return (0);
}

void	assign_forks(t_philo *philos, t_data *data)
{
	int		i;

	i = 0;
	while (i < data->nb_philo)
	{
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % data->nb_philo;
		i++;
	}
}

int	init_data(t_data *data, int argc, char **argv)
{
	memset(data, 0, sizeof(t_data));
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->stop = 0;
	if (argc == 6)
		data->nb_must_eat = ft_atoi(argv[5]);
	else
		data->nb_must_eat = -1;
	if (validate_philo_count(data->nb_philo))
		return (1);
	return (0);
}
