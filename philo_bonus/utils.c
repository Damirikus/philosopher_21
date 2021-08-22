/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <sdominqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 18:37:56 by sdominqu          #+#    #+#             */
/*   Updated: 2021/08/12 18:37:59 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

void	ft_free_all(void)
{
	sem_close(g_table->sem_forks);
	sem_close(g_table->sem_msg);
	sem_close(g_table->sem_dead);
	sem_close(g_table->sem_not);
	sem_close(g_table->sem_for_die);
	free(g_table->philosophers);
	free(g_table->id);
	free(g_table);
}

void	ft_init_time(void)
{
	int	i;

	i = 0;
	while (i < g_table->info.numbers_phil)
	{
		g_table->philosophers[i].last_eat = g_table->start_time;
		i++;
	}
}

int	ft_atoi(const char *str)
{
	int	nb;
	int	i;
	int	k;

	k = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			k = -1;
		else
			k = 1;
		i++;
	}
	nb = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		nb = 10 * nb + (str[i] - 48);
		i++;
	}
	return (nb * k);
}

void	ft_println(unsigned long long ms, int name, char *str)
{
	sem_wait(g_table->sem_msg);
	printf("%3lld ms #%d - %s\n", ms, name, str);
	sem_post(g_table->sem_msg);
}
