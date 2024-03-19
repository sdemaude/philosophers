/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:48:00 by sdemaude          #+#    #+#             */
/*   Updated: 2024/03/18 19:41:04 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_state(char *str, t_philo *philo)
{
	static pthread_mutex_t	print_mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&print_mutex);
	printf("%ld %d %s", get_time() - philo->start_sim_time,
		philo->philo_id, str);
	pthread_mutex_unlock(&print_mutex);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

bool	mod_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '+')
			return (false);
		i++;
	}
	return (true);
}

long	mod_atol(const char *nptr)
{
	int		i;
	long	n;

	i = 0;
	n = 0;
	while (nptr[i] == ' ' || nptr[i] == '\f' || nptr[i] == '\n'
		|| nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\v')
		i++;
	if (nptr[i] == '+')
		i++;
	if (!nptr[i])
		return (LONG_MAX);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = n * 10 + (nptr[i] - '0');
		if (n > INT_MAX)
			return (LONG_MAX);
		i++;
	}
	return (n);
}
