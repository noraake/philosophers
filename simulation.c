/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noakebli <noakebli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:20:47 by noakebli          #+#    #+#             */
/*   Updated: 2025/07/15 11:43:10 by noakebli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_simulation_stopped(t_data *data)
{
	int	stopped;

	pthread_mutex_lock(&data->check);
	stopped = data->stop;
	pthread_mutex_unlock(&data->check);
	return (stopped);
}

int	check_death(t_philo *philo, t_data *data)
{
	long long	current_time;
	long long	last_meal_time;
	long long	time_since_meal;

	current_time = get_time();
	pthread_mutex_lock(&philo->meal_time);
	last_meal_time = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_time);
	time_since_meal = current_time - last_meal_time;
	if (time_since_meal >= data->time_to_die)
	{
		pthread_mutex_lock(&data->check);
		if (!data->stop)
		{
			data->stop = 1;
			pthread_mutex_unlock(&data->check);
			pthread_mutex_lock(&data->write);
			printf("%lld %d died\n", current_time - data->start_time, philo->id);
			pthread_mutex_unlock(&data->write);
			return (1);
		}
		pthread_mutex_unlock(&data->check);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philo		*philos;
	t_data		*data;
	int			i;

	philos = (t_philo *)arg;
	data = philos[0].data;
	while (1)
	{
		if (is_simulation_stopped(data))
			break ;
		i = 0;
		while (i < data->nb_philo && !is_simulation_stopped(data))
		{
			if (check_death(&philos[i], data))
				return (NULL);
			i++;
		}
		if (check_meals(philos, data))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

int	start_simulation(t_philo *philos, t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	data->start_time = get_time();
	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_lock(&philos[i].meal_time);
		philos[i].last_meal = data->start_time;
		pthread_mutex_unlock(&philos[i].meal_time);
		if (pthread_create(&philos[i].thread, NULL, &philo_routine, &philos[i]))
			return (1);
	}
	if (pthread_create(&monitor_thread, NULL, &monitor, philos))
		return (1);
	pthread_mutex_lock(&data->flaag);
	data->flag = 1;
	pthread_mutex_unlock(&data->flaag);
	i = -1;
	while (++i < data->nb_philo)
		if (pthread_join(philos[i].thread, NULL))
			return (1);
	return (pthread_join(monitor_thread, NULL) != 0);
}
