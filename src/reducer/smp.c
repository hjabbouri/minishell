/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:29:35 by stamim            #+#    #+#             */
/*   Updated: 2022/10/25 12:12:05 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

static char	*path_join(t_pipln *pip)
{
	char	*str;
	size_t	len;

	len = ft_chr(pip->paths, ':', (int)ft_strlen(pip->paths));
	str = (char *)ft_malloc(sizeof(char *) * (len + ft_strlen(pip->name) + 2));
	if (str)
	{
		ft_strlcpy(str, pip->paths, len + 1);
		str[len] = '/';
		ft_strlcpy(str + 1 + len, pip->name, len + 1 + ft_strlen(pip->name));
	}
	pip->paths += len + 1;
	return (str);
}

static void	argv_ptr(t_pipln *pip)
{
	size_t	idx;
	t_token	*tkn;

	pip->argv = ft_malloc(sizeof(char *) * (pip->count + 1));
	if (pip->argv)
	{
		idx = 1;
		pip->argv[0] = pip->name;
		while (pip->wrds)
		{
			tkn = ft_pop_front(&pip->wrds);
			pip->argv[idx++] = tkn->wrd;
			free(tkn);
		}
		pip->argv[idx] = NULL;
	}
}

static void	redirect(t_pipln *pip)
{
	int	file;

	pip->opr = pip->head->opr;
	ft_lst_del_one(pip->head);
	pip->head = ft_pop_front(&pip->cmd);
	file = open_files(pip);
	ft_lst_del_one(pip->head);
	if (file == -1)
		(perror(NAME), pip->status = (errno << 8));
	if (pip->opr == IN || pip->opr == HEREDOC)
	{
		close(0);
		if (file > 0 && dup2(file, 0) == -1)
			(perror(NAME), pip->status = (errno << 8));
	}
	else
	{
		close(1);
		if (file > 0 && dup2(file, 1) == -1)
			(perror(NAME), pip->status = (errno << 8));
	}
	if (file > 0 && close(file) == -1)
		(perror(NAME), pip->status = (errno << 8));
}

static void	find_cmd(t_pipln *pip)
{
	pip->name = pip->wrds->wrd;
	pip->blt = (free(ft_pop_front(&pip->wrds)), find_blt(pip->name));
	argv_ptr(pip);
	if (pip->blt)
		return ;
	if (ft_strchr(pip->name, '/') && access(pip->name, F_OK | X_OK) == 0)
	{
		pip->exe = pip->name;
		if (pip->argv[1] == NULL)
			pip->e->str = (free(pip->e->str), ft_strjoin("_=", pip->exe));
		return ;
	}
	pip->paths = ft_getenv("PATH=", pip->e);
	while (pip->paths && *pip->paths)
	{
		pip->exe = path_join(pip);
		if (access(pip->exe, F_OK | X_OK) == 0)
			break ;
		pip->exe = (free(pip->exe), NULL);
	}
	if (!pip->exe || !*pip->name)
		ft_perror(pip->name, NOT_FOUND, NULL);
	else if (pip->argv[1] == NULL)
		pip->e->str = (free(pip->e->str), ft_strjoin("_=", pip->exe));
}

int	smp_cmd_exp(t_pipln *pip)
{
	while (pip->cmd)
	{
		pip->head = ft_pop_front(&pip->cmd);
		if (pip->head->type == WORD)
		{
			pip->e->str = (free(pip->e->str), ft_strjoin("_=", pip->head->wrd));
			ft_push_back(&pip->wrds, (pip->count++, pip->head));
			continue ;
		}
		redirect(pip);
	}
	if (!pip->wrds)
		return (clean(pip));
	find_cmd(pip);
	if (pip->blt)
		return (pip->status = pip->blt(pip->argv + 1, pip->e), clean(pip));
	if (!pip->exe || !*pip->name || pip->status)
		return (pip->status = 127 << 8, clean(pip));
	pip->pid = fork();
	if (pip->pid == -1)
		return (perror(NAME), pip->status = errno << 8, clean(pip));
	if (pip->pid == 0)
		(reset_signals(), execve(pip->exe, pip->argv, list2arr(pip->e)),
			perror(NAME), pip->status = errno << 8, exit(clean(pip)));
	return (waitpid(pip->pid, &pip->status, 0), clean(pip));
}
