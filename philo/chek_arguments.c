/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chek_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <sdominqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 16:45:52 by sdominqu          #+#    #+#             */
/*   Updated: 2021/08/12 16:45:55 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_chek_arguments(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (ft_error(RED"ERROR: Wrong number of arguments!"));
	i = 1;
	while (i < argc)
	{
		if (ft_isdigit(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_isdigit(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] < 48 || argv[i] > 57)
			return (ft_error(RED"ERROR: Wrong arguments!"));
		i++;
	}
	return (0);
}

void	ft_init_philosophers(void)
{
	int	i;

	i = 0;
	while (i < g_table->info.numbers_phil)
	{
		g_table->philosophers[i].amount_of_lunch = 0;
		g_table->philosophers[i].name = i + 1;
		g_table->philosophers[i].left_fork = i;
		if (i == 0)
			g_table->philosophers[i].right_fork = g_table->info.numbers_phil
				- 1;
		else
			g_table->philosophers[i].right_fork = i - 1;
		i++;
	}
}

int	ft_init(int argc, char **argv)
{
	if ((ft_atoi(argv[1])) == 0)
		return (ft_error(RED"Error: the number of philosophies is 0!"));
	g_table->info.numbers_phil = ft_atoi(argv[1]);
	g_table->info.time_to_die = ft_atoi(argv[2]);
	g_table->info.time_to_eat = ft_atoi(argv[3]);
	g_table->info.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		if ((ft_atoi(argv[5])) == 0)
			return (1);
		g_table->info.n_o_t_e_p_m_e = ft_atoi(argv[5]);
	}
	else
		g_table->info.n_o_t_e_p_m_e = -1;
	if (ft_init_helper())
		return (1);
	return (0);
}

int	ft_init_helper(void)
{
	int	i;

	g_table->philosophers = malloc(sizeof(t_phil) * g_table->info.numbers_phil);
	if (!g_table->philosophers)
		return (ft_error(RED"Error: failed to allocate memory!"));
	g_table->forks = malloc(sizeof(pthread_mutex_t)
			* g_table->info.numbers_phil);
	if (!g_table->forks)
		return (ft_error(RED"Error: failed to allocate memory!"));
	pthread_mutex_init(&g_table->msg, NULL);
	pthread_mutex_init(&g_table->die, NULL);
	i = 0;
	while (i < g_table->info.numbers_phil)
	{
		pthread_mutex_init(&g_table->forks[i], NULL);
		i++;
	}
	g_table->dead_flag = 0;
	return (0);
}
