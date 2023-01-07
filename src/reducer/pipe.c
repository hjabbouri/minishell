/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:59:58 by stamim            #+#    #+#             */
/*   Updated: 2022/10/25 11:59:54 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"
#include <sys/wait.h>

int	clean(t_pipln *pip)
{
	char		**tm1;
	char		*tm2;
	char *const	tm3 = pip->hrdcs;

	tm1 = pip->argv;
	while (tm1 && *tm1)
		free(*++tm1);
	(free(pip->argv), free(pip->envp), free(pip->name));
	if (pip->name != pip->exe)
		free(pip->exe);
	while (pip->hrdcs && *pip->hrdcs)
	{
		pip->count = ft_chr(pip->hrdcs, ':', (int)ft_strlen(pip->hrdcs));
		pip->hrdcs[pip->count] = '\0';
		tm2 = ft_malloc(sizeof(char *) * pip->count);
		if (!tm2)
			break ;
		(ft_strlcpy(tm2, pip->hrdcs, pip->count + 1), unlink(tm2), free(tm2));
		pip->hrdcs += pip->count + 1;
	}
	free(tm3);
	return (WEXITSTATUS(pip->status));
}

static void	fill_smp_cmd(t_pipln *pip, t_token **tkns)
{
	pip->cmd = NULL;
	while (tkns && *tkns)
	{
		pip->head = ft_pop_front(tkns);
		if ((pip->head)->type == OPERATOR && (pip->head)->opr == PIPE)
		{
			ft_lst_del_one(pip->head);
			pip->head = NULL;
			break ;
		}
		ft_push_back(&pip->cmd, pip->head);
	}
}

static void	get_pip_status(t_pipln *pip, t_token *tkns)
{
	while (true)
	{
		if (!tkns)
			pip->pipes[1] = 1;
		else if (pipe(pip->pipes) == -1)
			exit((perror(NAME), (errno << 8)));
		pip->pid = fork();
		if (pip->pid == -1)
			exit((perror(NAME), kill(-1, SIGINT), (errno << 8)));
		if (pip->pid == 0)
		{
			if (dup2(pip->stdin, 0) == -1 || dup2(pip->pipes[1], 1) == -1)
				(perror(NAME), exit((errno << 8)));
			exit((close(pip->pipes[0]), smp_cmd_exp(pip)));
		}
		if ((pip->pipes[1] != 1 && close(pip->pipes[1]) == -1)
			|| (pip->stdin != 0 && close(pip->stdin) == -1))
			exit((perror(NAME), (errno << 8)));
		pip->stdin = (ft_lst_del_all(pip->cmd), pip->pipes[0]);
		if (!tkns)
			break ;
		fill_smp_cmd(pip, &tkns);
	}
}

int	lst_pipe(t_pipln pip, t_token *tkns)
{
	fill_smp_cmd(&pip, &tkns);
	if (!tkns && pip.pid == -2)
		return (smp_cmd_exp(&pip));
	pip.pid = fork();
	if (pip.pid == -1)
		return (perror(NAME), pip.status = (errno << 8), clean(&pip));
	if (pip.pid == 0)
	{
		reset_signals();
		get_pip_status(&pip, tkns);
		waitpid(pip.pid, &pip.status, 0);
		while (wait(NULL) != -1)
			;
		free_env(pip.e);
		exit(clean(&pip));
	}
	ft_lst_del_all(pip.cmd);
	ft_lst_del_all(tkns);
	waitpid(pip.pid, &pip.status, 0);
	return (clean(&pip));
}
