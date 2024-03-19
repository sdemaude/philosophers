/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:49:10 by sdemaude          #+#    #+#             */
/*   Updated: 2024/03/18 16:20:16 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	to_think(t_philo *philo)
{
	if (end_sim(philo))
		return ;
	print_state("is thinking\n", philo);
}

void	to_sleep(t_philo *philo)
{
	if (end_sim(philo))
		return ;
	print_state("is sleeping\n", philo);
	usleep(philo->sim_arg.time_to_sleep);
}

void	fork_available(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->available = true;
	pthread_mutex_unlock(&fork->mutex);
}

bool	take_fork(t_philo *philo, t_fork *fork)
{
	while (!end_sim(philo))
	{
		pthread_mutex_lock(&fork->mutex);
		if (fork->available)
		{
			fork->available = false;
			pthread_mutex_unlock(&fork->mutex);
			if (end_sim(philo))
				return (false);
			print_state("has taken a fork\n", philo);
			return (true);
		}
		pthread_mutex_unlock(&fork->mutex);
		usleep(500);
	}
	return (false);
}

bool	to_eat(t_philo *philo)
{
	if (take_fork(philo, &philo->left_fork)
		&& take_fork(philo, philo->right_fork))
	{
		if (end_sim(philo))
			return (false);
		print_state("is eating\n", philo);
		philo->last_meal = get_time();
		usleep(philo->sim_arg.time_to_eat);
		fork_available(&philo->left_fork);
		fork_available(philo->right_fork);
		philo->meal_count++;
		if (end_sim(philo))
			return (false);
		if (philo->meal_count == philo->sim_arg.meals_limit)
			is_full(philo, true);
		return (true);
	}
	return (false);
}
