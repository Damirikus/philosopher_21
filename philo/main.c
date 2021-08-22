/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <sdominqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 16:45:59 by sdominqu          #+#    #+#             */
/*   Updated: 2021/08/12 16:46:02 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	time_difference(struct timeval old)
{
	struct timeval	new;

	gettimeofday(&new, NULL);
	new.tv_sec -= old.tv_sec;
	new.tv_usec -= old.tv_usec;
	if (new.tv_usec < 0)
	{
		--new.tv_sec;
		new.tv_usec += 1000000;
	}
	return ((new.tv_sec * 1000) + (new.tv_usec / 1000));
}

void	my_usleep(long time, struct timeval now)
{
	unsigned long long	cur_time;

	cur_time = time_difference(now);
	while (1)
	{
		usleep(100);
		if (time_difference(now) == cur_time + time)
			break ;
	}
}

int	main(int argc, char **argv)
{
	if (ft_chek_arguments(argc, argv))
		return (1);
	g_table = malloc(sizeof(t_table));
	if (!g_table)
		return (ft_error(RED"Error: failed to allocate memory!"));
	if (ft_init(argc, argv))
	{
		free(g_table);
		return (1);
	}
	ft_init_philosophers();
	if (ft_start())
	{
		ft_free_all();
		return (1);
	}
	ft_all_detach();
	ft_free_all();
	return (0);
}

void	ft_all_detach(void)
{
	int	i;

	i = 0;
	while (i < g_table->info.numbers_phil)
	{
		pthread_detach(g_table->philosophers[i].thread);
		i++;
	}
}

int	ft_start(void)
{
	int	i;

	gettimeofday(&g_table->start_time, NULL);
	ft_init_time();
	i = 0;
	while (i < g_table->info.numbers_phil)
	{
		if (pthread_create(&g_table->philosophers[i].thread, NULL, ft_eat,
				&g_table->philosophers[i]))
			return (ft_error(RED"Error: the thread was not created!"));
		usleep(50);
		i++;
	}
	ft_join(0, 0);
	return (0);
}
