/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:10:47 by hjabbour          #+#    #+#             */
/*   Updated: 2022/10/22 14:51:08 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

int	blt_env(char *args[], t_var *env)
{
	t_var	*tmp;

	(void)*args;
	if (!env)
		return (EXIT_FAILURE);
	if (env)
	{
		tmp = env;
		while (tmp)
		{
			if (ft_strchr(tmp->str, '='))
				printf("%s\n", tmp->str);
			tmp = tmp->next;
		}
	}
	return (EXIT_SUCCESS);
}
