#include "philo.h"

void	print_action(t_data *data, int id, char *action)
{
	pthread_mutex_lock(&(data->write));
	if (!data->stop)
		printf("%lld %d %s\n", get_time() - data->start_time, id, action);
	pthread_mutex_unlock(&(data->write));
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_action(philo->data, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_action(philo->data, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_action(philo->data, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_action(philo->data, philo->id, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_time);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_time);
	
	print_action(philo->data, philo->id, "is eating");
	philo->meals_eaten++;
	ft_sleep(philo->data->time_to_eat);
	
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	sleeping(t_philo *philo)
{
	print_action(philo->data, philo->id, "is sleeping");
	ft_sleep(philo->data->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_action(philo->data, philo->id, "is thinking");
}