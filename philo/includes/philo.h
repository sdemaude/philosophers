/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:07:46 by sdemaude          #+#    #+#             */
/*   Updated: 2024/03/18 16:19:59 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/time.h>

typedef struct s_fork
{
	int				fork_id;
	bool			available;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_sim_arg
{
	long	nb_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	meals_limit;
}	t_sim_arg;

typedef struct s_philo
{
	pthread_t	thread_id;
	int			philo_id;
	long		meal_count;
	long		last_meal;
	bool		full;
	t_fork		left_fork;
	t_fork		*right_fork;
	t_sim_arg	sim_arg;
	long		start_sim_time;
	bool		end_sim;
}	t_philo;

void	*start_routine(void *arg);

//UTILS (PHILO_UTILS)
void	ft_putstr_fd(char *s, int fd);
bool	mod_isdigit(char *str);
long	mod_atol(const char *nptr);
long	get_time(void);
void	print_state(char *str, t_philo *philo);

//INITILIZATION (INIT)
bool	init_arg(int nb_arg, char **arg_tab, t_sim_arg *sim_arg);
void	init_fork(t_fork *fork, int id);
void	init_philo(t_sim_arg *sim_arg, t_philo *philo, int id);
bool	init_sim(t_sim_arg *sim_arg);

//ROUTINE FONCTIONS (ROUTINE)
bool	to_eat(t_philo *philo);
void	to_sleep(t_philo *philo);
void	to_think(t_philo *philo);

//SIMULATION (PHILO)
bool	end_sim(t_philo *philo);

bool	is_full(t_philo *philo, bool eat);

#endif
