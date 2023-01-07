/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:59:20 by hjabbour          #+#    #+#             */
/*   Updated: 2022/10/23 16:33:16 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

static int	get_status(char *arg)
{
	int			ans;
	bool		neg;
	const char	*num = arg;

	ans = 0;
	neg = false;
	if (*num == '-' || *num == '+')
	{
		neg = true;
		num += 1;
		if (!*num)
			return (-1);
	}
	while (*num)
	{
		if (!ft_isdigit(*num))
			return (ft_perror(EX_NAME, arg, NUM_REQ), EXIT_FAILURE);
		ans = ans * BASE + *num++ - '0';
	}
	if (neg)
		return (-ans);
	return (ans);
}

int	blt_exit(char *args[], t_var *env)
{
	int	status;

	(void)env;
	if (!*args)
		status = EXIT_SUCCESS;
	else
	{
		if (!args[1])
			status = get_status(*args);
		else
		{
			ft_perror(EX_NAME, args[0], EXCEEDED_ARGS);
			status = EXIT_FAILURE;
		}
	}
	free_env(env);
	exit(status);
}
