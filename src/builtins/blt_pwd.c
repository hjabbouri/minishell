/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:10:28 by hjabbour          #+#    #+#             */
/*   Updated: 2022/10/25 12:43:47 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

int	blt_pwd(char *args[], t_var *env)
{
	char *const	buf = getcwd((char [PATH_MAX]){'\0'}, PATH_MAX);

	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	return ((void)args, (void)env, (EXIT_SUCCESS));
}
