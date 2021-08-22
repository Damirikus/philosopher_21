/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <sdominqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 16:45:39 by sdominqu          #+#    #+#             */
/*   Updated: 2021/08/12 16:45:42 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <semaphore.h>
# include <pthread.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/time.h>

# define RED "\x1B[31m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define GREEN "\x1B[32m"
# define PINK "\x1B[35m"
# define WHITE "\x1B[37m"

typedef struct s_info
{
	int	numbers_phil;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_o_t_e_p_m_e;
}		t_info;

typedef struct s_phil
{
	int				name;
	unsigned int	left_fork;
	unsigned int	right_fork;
	pthread_t		thread;
	struct timeval	last_eat;
	int				amount_of_lunch;

}					t_phil;

typedef struct s_table
{
	t_info			info;
	pthread_mutex_t	*forks;
	pthread_mutex_t	msg;
	pthread_mutex_t	die;
	t_phil			*philosophers;
	struct timeval	start_time;
	int				dead_flag;

}					t_table;

t_table	*g_table;
int					ft_chek_arguments(int argc, char **argv);
int					ft_error(char *str);
int					ft_isdigit(char *argv);
int					ft_atoi(const char *str);
int					ft_init(int argc, char **argv);
void				my_usleep(long time, struct timeval now);
void				ft_println(unsigned long long ms, int name, char *str);
void				ft_init_philosophers(void);
void				*ft_eat(void *args);
int					ft_start(void);
unsigned long long	time_difference(struct timeval old);
void				ft_init_time(void);
void				ft_free_all(void);
void				ft_all_detach(void);
int					ft_join(int k, int count);
int					ft_init_helper(void);
void				ft_eat_helper(t_phil *philosopher);
void				ft_eat_part_helper(t_phil *philosopher);
int					ft_join_helper(int k);
#endif