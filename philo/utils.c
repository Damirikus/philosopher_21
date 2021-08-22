/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <sdominqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 16:46:21 by sdominqu          #+#    #+#             */
/*   Updated: 2021/08/12 16:46:23 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_mutex_lock(&g_table->msg);
	printf("%lld ms", ms);
	printf(" #%d - %s\n", name, str);
	pthread_mutex_unlock(&g_table->msg);
}

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

void	ft_free_all(void)
{
	int	i;

	pthread_mutex_destroy(&g_table->msg);
	pthread_mutex_destroy(&g_table->die);
	i = 0;
	while (i < g_table->info.numbers_phil)
	{
		pthread_mutex_destroy(&g_table->forks[i]);
		i++;
	}
	free(g_table->philosophers);
	free(g_table->forks);
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
