/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_meals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noakebli <noakebli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 01:53:52 by noakebli          #+#    #+#             */
/*   Updated: 2025/07/25 05:00:29 by noakebli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	count_finished_meals(t_philo *philos, t_data *data)
{
	int		i;
	int		finished;

	i = 0;
	finished = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&philos[i].meal_time);
		if (philos[i].meals_eaten >= data->nb_must_eat)
			finished++;
		pthread_mutex_unlock(&philos[i].meal_time);
		i++;
	}
	return (finished);
}

int	check_meals(t_philo *philos, t_data *data)
{
	int		finished;

	if (data->nb_must_eat == -1)
		return (0);
	finished = count_finished_meals(philos, data);
	if (finished == data->nb_philo)
	{
		pthread_mutex_lock(&data->check);
		if (!data->stop)
		{
			data->stop = 1;
			pthread_mutex_unlock(&data->check);
			return (1);
		}
		pthread_mutex_unlock(&data->check);
	}
	return (0);
}
