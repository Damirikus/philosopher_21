/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <sdominqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 18:37:42 by sdominqu          #+#    #+#             */
/*   Updated: 2021/08/12 18:37:44 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	if (ft_init(argc, argv) == 1)
	{
		free(g_table);
		return (1);
	}
	else if (ft_init(argc, argv) == 2)
	{
		free(g_table->philosophers);
		free(g_table);
		return (1);
	}
	ft_init_philosophers();
	ft_start();
	ft_free_all();
	return (0);
}

void	*ft_wait_fed(void *args)
{
	t_table	*tab;
	int		i;

	tab = (t_table *)args;
	i = 0;
	if (g_table->info.n_o_t_e_p_m_e != -1)
	{
		while (i < tab->info.numbers_phil)
		{
			sem_wait(g_table->sem_not);
			i++;
		}
		sem_post(g_table->sem_dead);
	}
	return (args);
}

void	*ft_monit(void *args)
{
	t_phil	*philosopher;

	philosopher = (t_phil *)args;
	while (1)
	{
		sem_wait(g_table->sem_for_die);
		if (time_difference(philosopher->last_eat) > g_table->info.time_to_die)
		{
			ft_println(time_difference(g_table->start_time), philosopher->name,
				RED"died");
			sem_post(g_table->sem_dead);
			exit(0);
		}
		sem_post(g_table->sem_for_die);
	}
}
