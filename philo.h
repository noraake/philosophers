#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	int				stop;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	check;
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
void		take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		sleeping(t_philo *philo);
void		think(t_philo *philo);

/* Simulation */
int			start_simulation(t_philo *philos, t_data *data);
void		*philo_routine(void *arg);
void		*monitor(void *arg);
int			check_death(t_philo *philo, t_data *data);
int			check_meals(t_philo *philos, t_data *data);

/* Utils */
void		free_all(t_philo *philos, t_data *data);

#endif