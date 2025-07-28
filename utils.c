/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noakebli <noakebli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:20:58 by noakebli          #+#    #+#             */
/*   Updated: 2025/04/28 10:20:58 by noakebli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_data *data, int id, char *action)
{
	pthread_mutex_lock(&(data->check));
	if (!data->stop)
	{
		pthread_mutex_lock(&(data->write));
		printf("%lld %d %s\n", get_time() - data->start_time, id, action);
		pthread_mutex_unlock(&(data->write));
	}
	pthread_mutex_unlock(&data->check);
}

void	free_all(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&philos[i].meal_time);
		i++;
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->check);
	pthread_mutex_destroy(&data->flaag);
	free(data->forks);
	free(philos);
}
