/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:47:10 by sdemaude          #+#    #+#             */
/*   Updated: 2024/03/18 19:22:10 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	is_tab_digit(char **arg_tab)
{
	int	i;

	i = 0;
	while (arg_tab[i])
	{
		if (!mod_isdigit(arg_tab[i]))
			return (false);
		i++;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_sim_arg	sim_arg;

	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("Incorrect number of argument\n", STDERR_FILENO);
		return (1);
	}
	if (!is_tab_digit(++argv) || !init_arg(--argc, argv, &sim_arg))
	{
		ft_putstr_fd("Argument not valid\n", STDERR_FILENO);
		return (1);
	}
	if (!init_sim(&sim_arg))
	{
		ft_putstr_fd("Could not create the thread or mutex\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
