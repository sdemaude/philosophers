/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:26:41 by sdemaude          #+#    #+#             */
/*   Updated: 2024/03/18 19:39:51 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	init_arg(int nb_arg, char **arg_tab, t_sim_arg *sim_arg)
{
	sim_arg->nb_philos = mod_atol(arg_tab[0]);
	if (sim_arg->nb_philos == LONG_MAX || sim_arg->nb_philos == 0)
		return (false);
	sim_arg->time_to_die = mod_atol(arg_tab[1]);
	if (sim_arg->time_to_die == LONG_MAX)
		return (false);
	sim_arg->time_to_eat = mod_atol(arg_tab[2]);
	if (sim_arg->time_to_eat == LONG_MAX)
		return (false);
	sim_arg->time_to_sleep = mod_atol(arg_tab[3]);
	if (sim_arg->time_to_sleep == LONG_MAX)
		return (false);
	if (nb_arg == 5)
	{
		sim_arg->meals_limit = mod_atol(arg_tab[4]);
		if (sim_arg->meals_limit == LONG_MAX)
			return (false);
	}
	else
		sim_arg->meals_limit = -1;
	sim_arg->time_to_die *= 1000;
	sim_arg->time_to_eat *= 1000;
	sim_arg->time_to_sleep *= 1000;
	return (true);
}

void	init_fork(t_fork *fork, int id)
{
	fork->available = true;
	fork->fork_id = id - 1;
	pthread_mutex_init(&fork->mutex, NULL);
}

void	init_philo(t_sim_arg *sim_arg, t_philo *philo, int id)
{
	philo->philo_id = id;
	init_fork(&philo->left_fork, id);
	philo->right_fork = NULL;
	philo->sim_arg = *sim_arg;
	philo->full = false;
	philo->end_sim = false;
	philo->last_meal = 0;
	philo->meal_count = 0;
	philo->start_sim_time = 0;
}

bool	init_sim(t_sim_arg *sim_arg)
{
	t_philo	*philo_tab;
	int		i;

	i = 0;
	philo_tab = malloc(sizeof(t_philo) * sim_arg->nb_philos);
	init_philo(sim_arg, &philo_tab[i], i + 1);
	while (++i < sim_arg->nb_philos)
	{
		init_philo(sim_arg, &philo_tab[i], i + 1);
		philo_tab[i - 1].right_fork = &philo_tab[i].left_fork;
		pthread_create(&philo_tab[i - 1].thread_id,
			NULL, &start_routine, &philo_tab[i - 1]);
	}
	philo_tab[i - 1].right_fork = &philo_tab[0].left_fork;
	pthread_create(&philo_tab[i - 1].thread_id,
		NULL, &start_routine, &philo_tab[i - 1]);
	i = -1;
	while (++i < sim_arg->nb_philos)
		pthread_join(philo_tab[i].thread_id, NULL);
	free(philo_tab);
	return (true);
}
