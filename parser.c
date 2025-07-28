/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noakebli <noakebli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:21:08 by noakebli          #+#    #+#             */
/*   Updated: 2025/04/28 10:21:08 by noakebli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long long	nbr;
	int			i;

	i = 0;
	nbr = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		if (nbr <= INT_MIN)
			return (0);
		i++;
	}
	return (nbr);
}

int	is_digit_string(char *str)
{
	int	j;

	if (!str[0])
	{
		printf("Error: Arguments must be positive integers\n");
		return (0);
	}
	j = 0;
	if (str[j] == '+')
		j++;
	if (!str[j])
	{
		printf("Error: Arguments must be positive integers\n");
		return (0);
	}
	while (str[j])
	{
		if (str[j] < '0' || str[j] > '9')
		{
			printf("Error: Arguments must be positive integers\n");
			return (0);
		}
		j++;
	}
	return (1);
}

int	is_valid_number(char *str)
{
	long	num;

	if (!is_digit_string(str))
		return (0);
	num = ft_atoi(str);
	if (num <= 0 || num > INT_MAX)
	{
		printf("Error: Arguments must be positive integers\n");
		return (0);
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

int	validate_philo_count(int nb_philo)
{
	if (nb_philo <= 0 || nb_philo > 200)
	{
		printf("Error: Invalid number of philosophers\n");
		return (1);
	}
	return (0);
}
