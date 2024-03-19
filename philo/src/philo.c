/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 10:52:02 by sdemaude          #+#    #+#             */
/*   Updated: 2024/03/18 19:21:50 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	will_they_die(t_philo *philo)
{
	if (philo->sim_arg.time_to_eat >= philo->sim_arg.time_to_die)
		return (true);
	if (philo->sim_arg.time_to_sleep >= philo->sim_arg.time_to_die)
		return (true);
	return (false);
}

bool	is_dead(t_philo *philo)
{
	if (get_time() - philo->last_meal >= philo->sim_arg.time_to_die / 1000)
	{
		print_state("is dead\n", philo);
		return (true);
	}
	return (false);
}

bool	is_full(t_philo *philo, bool eat)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	static long				philo_full;

	pthread_mutex_lock(&mutex);
	if (eat && philo->meal_count == philo->sim_arg.meals_limit)
		philo_full++;
	if (philo->sim_arg.nb_philos == philo_full)
	{
		pthread_mutex_unlock(&mutex);
		return (true);
	}
	pthread_mutex_unlock(&mutex);
	return (false);
}

bool	end_sim(t_philo *philo)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	static bool				finish;

	pthread_mutex_lock(&mutex);
	if (finish)
	{
		pthread_mutex_unlock(&mutex);
		return (true);
	}
	if (is_dead(philo) || is_full(philo, false))
		finish = true;
	pthread_mutex_unlock(&mutex);
	return (false);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	philo->start_sim_time = get_time();
	philo->last_meal = philo->start_sim_time;
	if (!(philo->philo_id % 2))
	{
		to_think(philo);
		if (will_they_die(philo))
			usleep(philo->sim_arg.time_to_die);
		else
			usleep(philo->sim_arg.time_to_eat);
	}
	while (!end_sim(philo))
	{
		if (philo->meal_count > 0 || philo->philo_id % 2)
			to_think(philo);
		if (to_eat(philo))
			to_sleep(philo);
	}
	return (NULL);
}
