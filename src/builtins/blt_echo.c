/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stamim <stamim@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:57:53 by hjabbour          #+#    #+#             */
/*   Updated: 2022/10/21 18:13:31 by stamim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

static bool	prohibit_nwln(const char *first)
{
	if (!first || *first != '-' || !first[1])
		return (false);
	while (*++first)
		if (*first != 'n')
			return (false);
	return (true);
}

int	blt_echo(char *args[], t_var *env)
{
	const bool	no_nwln_arg = prohibit_nwln(*args);

	if (no_nwln_arg)
		args += 1;
	while (*args)
	{
		if (args[1])
			printf("%s ", *args);
		else
			printf("%s", *args);
		args += 1;
	}
	if (!no_nwln_arg)
		printf("\n");
	(void)env;
	return (EXIT_SUCCESS);
}
