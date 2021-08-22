/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chek_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <sdominqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 18:37:34 by sdominqu          #+#    #+#             */
/*   Updated: 2021/08/12 18:37:37 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		i++;
	}
}

int	ft_init(int argc, char **argv)
{
	if (ft_atoi(argv[1]) == 0)
		return (ft_error(RED"Error: the number of philosophies is 0!"));
	g_table->info.numbers_phil = ft_atoi(argv[1]);
	g_table->info.time_to_die = ft_atoi(argv[2]);
	g_table->info.time_to_eat = ft_atoi(argv[3]);
	g_table->info.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) == 0)
			return (1);
		g_table->info.n_o_t_e_p_m_e = ft_atoi(argv[5]);
	}
	else
		g_table->info.n_o_t_e_p_m_e = -1;
	g_table->philosophers = malloc(sizeof(t_phil) * g_table->info.numbers_phil);
	if (!g_table->philosophers)
		return (ft_error(RED"Error: the number of philosophies is 0!"));
	g_table->id = malloc(sizeof(pid_t) * g_table->info.numbers_phil);
	if (!g_table->id)
	{
		printf(RED"Error: the number of philosophies is 0!");
		return (2);
	}
	ft_init_helper();
	return (0);
}

void	ft_init_helper(void)
{
	sem_unlink("sem_forks");
	sem_unlink("sem_msg");
	sem_unlink("sem_all");
	sem_unlink("sem_dead");
	sem_unlink("sem_not");
	sem_unlink("sem_for_die");
	g_table->sem_forks = sem_open("sem_forks", O_CREAT, 0777,
			g_table->info.numbers_phil);
	g_table->sem_msg = sem_open("sem_msg", O_CREAT, 0777, 1);
	g_table->sem_all = sem_open("sem_all", O_CREAT, 0777, 1);
	g_table->sem_dead = sem_open("sem_dead", O_CREAT, 0777, 0);
	g_table->sem_not = sem_open("sem_not", O_CREAT, 0777, 0);
	g_table->sem_for_die = sem_open("sem_for_die", O_CREAT, 0777, 1);
	g_table->dead_flag = 0;
}
