#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->meal_time);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_time);
	
	if (philo->data->nb_philo == 1)
	{
		print_action(philo->data, philo->id, "has taken a fork");
		ft_sleep(philo->data->time_to_die);
		return (NULL);
	}
	
	if (philo->id % 2 == 0)
		ft_sleep(philo->data->time_to_eat / 2);
		
	while (!philo->data->stop)
	{
		take_forks(philo);
		eat(philo);
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}

int	check_death(t_philo *philo, t_data *data)
{
	long long	time;

	pthread_mutex_lock(&philo->meal_time);
	time = time_diff(philo->last_meal, get_time());
	pthread_mutex_unlock(&philo->meal_time);
	
	if (time > data->time_to_die)
	{
		pthread_mutex_lock(&data->check);
		if (!data->stop)
		{
			data->stop = 1;
			pthread_mutex_unlock(&data->check);
			pthread_mutex_lock(&data->write);
			printf("%lld %d died\n", 
				get_time() - data->start_time, philo->id);
			pthread_mutex_unlock(&data->write);
			return (1);
		}
		pthread_mutex_unlock(&data->check);
	}
	return (0);
}

int	check_meals(t_philo *philos, t_data *data)
{
	int	i;
	int	finished;

	if (data->nb_must_eat == -1)
		return (0);
	i = 0;
	finished = 0;
	while (i < data->nb_philo)
	{
		if (philos[i].meals_eaten >= data->nb_must_eat)
			finished++;
		i++;
	}
	if (finished == data->nb_philo)
	{
		pthread_mutex_lock(&data->check);
		data->stop = 1;
		pthread_mutex_unlock(&data->check);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philo	*philos;
	t_data	*data;
	int		i;

	philos = (t_philo *)arg;
	data = philos[0].data;
	while (!data->stop)
	{
		i = 0;
		while (i < data->nb_philo && !data->stop)
		{
			if (check_death(&philos[i], data))
				return (NULL);
			i++;
		}
		if (check_meals(philos, data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

int	start_simulation(t_philo *philos, t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	data->start_time = get_time();
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&(philos[i].thread), NULL, 
				&philo_routine, &(philos[i])))
			return (1);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, &monitor, philos))
		return (1);
	
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(philos[i].thread, NULL))
			return (1);
		i++;
	}
	if (pthread_join(monitor_thread, NULL))
		return (1);
	return (0);
}