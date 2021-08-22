/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realization.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <sdominqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 16:46:14 by sdominqu          #+#    #+#             */
/*   Updated: 2021/08/12 18:47:19 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_join(int k, int count)
{
	while (!(g_table->dead_flag))
	{
		k = 0;
		count = 0;
		while (k < g_table->info.numbers_phil)
		{
			if (time_difference(g_table->philosophers[k].last_eat)
				> (unsigned long long)g_table->info.time_to_die)
				return (ft_join_helper(k));
			if (g_table->info.n_o_t_e_p_m_e != -1)
			{
				if (g_table->philosophers[k].amount_of_lunch
					>= g_table->info.n_o_t_e_p_m_e)
					count++;
				if (count == g_table->info.numbers_phil)
					return (0);
			}
			k++;
		}
	}
	return (0);
}

int	ft_join_helper(int k)
{
	pthread_mutex_lock(&g_table->die);
	ft_println(time_difference(g_table->start_time),
		g_table->philosophers[k].name, RED"died");
	g_table->dead_flag++;
	pthread_mutex_unlock(&g_table->die);
	return (0);
}

void	*ft_eat(void *args)
{
	t_phil	*philosopher;

	philosopher = (t_phil *)args;
	while (1)
	{
		if (philosopher->name % 2 == 1)
		{
			pthread_mutex_lock(&g_table->forks[philosopher->left_fork]);
			ft_println(time_difference(g_table->start_time), philosopher->name,
				BLUE"has taken a left fork"WHITE);
			pthread_mutex_lock(&g_table->forks[philosopher->right_fork]);
			ft_println(time_difference(g_table->start_time), philosopher->name,
				BLUE"has taken a right fork"WHITE);
		}
		else
			ft_eat_part_helper(philosopher);
		ft_eat_helper(philosopher);
	}
}

void	ft_eat_part_helper(t_phil *philosopher)
{
	pthread_mutex_lock(&g_table->forks[philosopher->right_fork]);
	ft_println(time_difference(g_table->start_time), philosopher->name,
		BLUE"has taken a right fork"WHITE);
	pthread_mutex_lock(&g_table->forks[philosopher->left_fork]);
	ft_println(time_difference(g_table->start_time), philosopher->name,
		BLUE"has taken a left fork"WHITE);
}

void	ft_eat_helper(t_phil *philosopher)
{
	gettimeofday(&g_table->philosophers[philosopher->name - 1].last_eat, NULL);
	ft_println(time_difference(g_table->start_time), philosopher->name,
		GREEN"is eating"WHITE);
	g_table->philosophers[philosopher->name - 1].amount_of_lunch++;
	my_usleep(g_table->info.time_to_eat, g_table->start_time);
	pthread_mutex_unlock(&g_table->forks[philosopher->left_fork]);
	pthread_mutex_unlock(&g_table->forks[philosopher->right_fork]);
	ft_println(time_difference(g_table->start_time), philosopher->name,
		PINK"is sleeping"WHITE);
	my_usleep(g_table->info.time_to_sleep, g_table->start_time);
	ft_println(time_difference(g_table->start_time), philosopher->name,
		YELLOW"is thinking"WHITE);
}
