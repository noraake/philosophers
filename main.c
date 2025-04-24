#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Invalid number of arguments\n");
		return (1);
	}
	if (check_args(argc, argv))
		return (1);
	if (init_data(&data, argc, argv))
		return (1);
	if (init_mutexes(&data))
		return (1);
	if (init_philos(&philos, &data))
		return (1);
	assign_forks(philos, &data);
	if (start_simulation(philos, &data))
		return (1);
	free_all(philos, &data);
	return (0);
}