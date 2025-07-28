/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noakebli <noakebli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:20:54 by noakebli          #+#    #+#             */
/*   Updated: 2025/04/28 10:20:54 by noakebli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_sleep(long long time)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(500);
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}
