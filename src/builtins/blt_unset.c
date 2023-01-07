/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:59:07 by hjabbour          #+#    #+#             */
/*   Updated: 2022/10/23 15:56:19 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"
#include <stdbool.h>
#include <stdlib.h>

static void	to_delelte(char *args, t_var *env)
{
	t_var	*ptr;
	t_var	*befor;
	t_var	*next;

	befor = env;
	env = env->next;
	while (env)
	{
		if (compare(args, env->str))
		{
			ptr = env;
			next = env->next;
			deallocate_node_env(ptr);
			befor->next = next;
			break ;
		}
		befor = env;
		env = env->next;
	}
}

int	blt_unset(char *args[], t_var *env)
{
	int	idx;

	idx = 0;
	while (args[idx])
	{
		if (!ft_chr(args[idx], '=', 0))
			to_delelte(args[idx], env);
		idx++;
	}
	return (EXIT_SUCCESS);
}
