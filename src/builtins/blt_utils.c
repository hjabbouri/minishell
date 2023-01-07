/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 08:56:25 by hjabbour          #+#    #+#             */
/*   Updated: 2022/10/19 16:03:13 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

t_blt	*find_blt(const char *blt)
{
	if (!blt)
		return (NULL);
	if (!ft_strncmp(blt, "cd", 3))
		return (blt_cd);
	if (!ft_strncmp(blt, "echo", 5))
		return (blt_echo);
	if (!ft_strncmp(blt, "env", 4))
		return (blt_env);
	if (!ft_strncmp(blt, "exit", 5))
		return (blt_exit);
	if (!ft_strncmp(blt, "export", 7))
		return (blt_export);
	if (!ft_strncmp(blt, "pwd", 4))
		return (blt_pwd);
	if (!ft_strncmp(blt, "unset", 6))
		return (blt_unset);
	return (NULL);
}

void	ft_perror(const char *cmd, char *arg, char *msg)
{
	write(STDERR_FILENO, NAME SEP, sizeof(NAME SEP));
	if (cmd)
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
	if (arg)
		write(STDERR_FILENO, arg, ft_strlen(arg));
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", sizeof(char));
}
