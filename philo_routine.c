/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noakebli <noakebli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:00:37 by noakebli          #+#    #+#             */
/*   Updated: 2025/07/28 16:40:16 by noakebli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_forks_if_needed(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	if (philo->left_fork < philo->right_fork)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_unlock(&philo->data->forks[second_fork]);
	pthread_mutex_unlock(&philo->data->forks[first_fork]);
}

void	relase_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

int	is_flag_set(t_data *data)
{
	int	flag_value;

	pthread_mutex_lock(&data->flaag);
	flag_value = data->flag;
	pthread_mutex_unlock(&data->flaag);
	return (flag_value);
}

void	philo_lifecycle(t_philo *philo)
{
	while (!is_simulation_stopped(philo->data))
	{
		if (!take_forks(philo))
			break ;
		if (is_simulation_stopped(philo->data))
		{
			relase_forks(philo);
			break ;
		}
		eat(philo);
		if (is_simulation_stopped(philo->data))
			break ;
		sleeping(philo);
		if (is_simulation_stopped(philo->data))
			break ;
		think(philo);
	}
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->meal_time);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_time);
	if (philo->data->nb_philo == 1)
	{
		pthread_mutex_lock(&philo->data->forks[0]);
		print_action(philo->data, philo->id, "has taken a fork");
		ft_sleep(philo->data->time_to_die);
		pthread_mutex_unlock(&philo->data->forks[0]);
		return (NULL);
	}
	while (!is_flag_set(philo->data))
		usleep (1);
	if (philo->id % 2 == 0)
		usleep(1000);
	philo_lifecycle(philo);
	return (NULL);
}
