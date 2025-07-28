/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noakebli <noakebli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:48:24 by noakebli          #+#    #+#             */
/*   Updated: 2025/07/21 11:48:24 by noakebli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lock_first_fork(t_philo *philo, int fork)
{
	pthread_mutex_lock(&philo->data->forks[fork]);
	if (is_simulation_stopped(philo->data))
	{
		pthread_mutex_unlock(&philo->data->forks[fork]);
		return (0);
	}
	print_action(philo->data, philo->id, "has taken a fork");
	return (1);
}

int	take_forks(t_philo *philo)
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
	if (!lock_first_fork(philo, first_fork))
		return (0);
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	if (is_simulation_stopped(philo->data))
	{
		pthread_mutex_unlock(&philo->data->forks[second_fork]);
		pthread_mutex_unlock(&philo->data->forks[first_fork]);
		return (0);
	}
	print_action(philo->data, philo->id, "has taken a fork");
	return (1);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_time);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_time);
	print_action(philo->data, philo->id, "is eating");
	if (philo->data->time_to_eat >= philo->data->time_to_die)
		ft_sleep(philo->data->time_to_die);
	else
		ft_sleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	sleeping(t_philo *philo)
{
	print_action(philo->data, philo->id, "is sleeping");
	if (philo->data->time_to_sleep >= philo->data->time_to_die)
		ft_sleep(philo->data->time_to_die);
	else
		ft_sleep(philo->data->time_to_sleep);
}

void	think(t_philo *philo)
{
	long long	think_time;

	print_action(philo->data, philo->id, "is thinking");
	if (philo->data->nb_philo % 2 == 1)
	{
		think_time = philo->data->time_to_eat * 2 - philo->data->time_to_sleep;
		if (think_time > 0)
			usleep(think_time * 1000);
		else
			usleep(1000);
	}
}
