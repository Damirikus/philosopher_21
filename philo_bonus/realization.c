/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realization.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <sdominqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 18:37:50 by sdominqu          #+#    #+#             */
/*   Updated: 2021/08/12 18:37:52 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_start(void)
{
	int			i;
	pthread_t	control_fed;

	pthread_create(&control_fed, NULL, &ft_wait_fed, g_table);
	gettimeofday(&g_table->start_time, NULL);
	ft_init_time();
	i = 0;
	while (i < g_table->info.numbers_phil)
	{
		g_table->id[i] = fork();
		if (g_table->id[i] == 0)
			ft_eat(&g_table->philosophers[i]);
		else if (g_table->id[i] < 0)
			exit(ft_error(RED"Error: fork failed"));
		i++;
	}
	sem_wait(g_table->sem_dead);
	ft_start_helper(0);
	pthread_detach(control_fed);
	return (0);
}

void	ft_start_helper(int i)
{
	while (i < g_table->info.numbers_phil)
	{
		kill(g_table->id[i], SIGKILL);
		i++;
	}
	i = g_table->info.n_o_t_e_p_m_e;
	g_table->info.n_o_t_e_p_m_e = -1;
	while (--i >= 0)
		sem_post(g_table->sem_not);
}

void	*ft_eat(void *args)
{
	t_phil		*philosopher;
	pthread_t	thread;

	philosopher = (t_phil *)args;
	if (pthread_create(&thread, NULL, ft_monit, args) != 0)
		return (NULL);
	while (1)
	{
		ft_sem_wait();
		ft_println(time_difference(g_table->start_time), philosopher->name,
			BLUE"has taken a left fork"WHITE);
		gettimeofday(&g_table->philosophers[philosopher->name - 1].last_eat,
			NULL);
		sem_wait(g_table->sem_forks);
		ft_println(time_difference(g_table->start_time), philosopher->name,
			BLUE"has taken a right fork"WHITE);
		sem_post(g_table->sem_all);
		ft_println(time_difference(g_table->start_time), philosopher->name,
			GREEN"is eating"WHITE);
		philosopher->amount_of_lunch++;
		if (g_table->info.n_o_t_e_p_m_e != -1)
			if (philosopher->amount_of_lunch >= g_table->info.n_o_t_e_p_m_e)
				sem_post(g_table->sem_not);
		ft_eat_helper(philosopher);
	}
}

void	ft_sem_wait(void)
{
	sem_wait(g_table->sem_all);
	sem_wait(g_table->sem_forks);
}

void	ft_eat_helper(t_phil *philosopher)
{
	my_usleep(g_table->info.time_to_eat, g_table->start_time);
	sem_post(g_table->sem_forks);
	sem_post(g_table->sem_forks);
	ft_println(time_difference(g_table->start_time), philosopher->name,
		PINK"is sleeping"WHITE);
	my_usleep(g_table->info.time_to_sleep, g_table->start_time);
	ft_println(time_difference(g_table->start_time), philosopher->name,
		YELLOW"is thinking"WHITE);
}
