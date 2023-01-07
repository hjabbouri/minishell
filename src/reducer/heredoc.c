/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:36:36 by hjabbour          #+#    #+#             */
/*   Updated: 2022/10/25 12:56:33 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>

char	*name_heredoc(char *del)
{
	char	*tmp;
	char	*ptr;
	char	*name;

	ptr = ft_ptrtoa(del);
	tmp = ft_strjoin("/tmp/.", ptr);
	name = ft_strjoin(tmp, ".tmp");
	free(tmp);
	free(ptr);
	return (name);
}

static void	save_files_name(t_pipln *pip, char *name)
{
	char	*tmp;

	if (!pip->hrdcs)
		pip->hrdcs = ft_strjoin(name, "");
	else
	{
		tmp = ft_strjoin(pip->hrdcs, ":");
		free(pip->hrdcs);
		pip->hrdcs = ft_strjoin(tmp, name);
		free(tmp);
	}
}

int	open_files(t_pipln *pip)
{
	char	*name;
	int		file;

	if (pip->opr == IN)
		file = open(pip->head->wrd, O_RDONLY | O_CLOEXEC, S_IRWXU);
	else if (pip->opr == OUT)
		file = open(pip->head->wrd,
				O_CREAT | O_WRONLY | O_CLOEXEC, S_IRWXU);
	else if (pip->opr == HEREDOC)
	{
		name = name_heredoc(pip->head->wrd);
		save_files_name(pip, name);
		file = open(name, O_CREAT | O_RDONLY | O_CLOEXEC, S_IRWXU);
		free(name);
	}
	else
		file = open(pip->head->wrd,
				O_CREAT | O_WRONLY | O_APPEND | O_CLOEXEC, S_IRWXU);
	return (file);
}

bool	open_heredoc(char *del)
{
	char		*line;
	char *const	name = name_heredoc(del);
	int			hrdc;

	unlink(name);
	hrdc = open(name, O_CREAT | O_TRUNC | O_WRONLY | O_CLOEXEC, S_IRWXU);
	free(name);
	if (hrdc == -1)
		exit ((ft_itoa(g_s, errno << 8), perror(NAME), EXIT_FAILURE));
	while (true)
	{
		line = readline(PROMPT_HRDC);
		if (!line)
			break ;
		if (line && !ft_strncmp(line, del, ft_strlen(del) + 1))
			break ;
		write(hrdc, line, ft_strlen(line));
		if (line)
			write(hrdc, "\n", 1);
		free(line);
	}
	free(line);
	if (close(hrdc) == -1)
		exit ((perror(NAME), ft_itoa(g_s, errno << 8), EXIT_FAILURE));
	exit (EXIT_SUCCESS);
}

bool	heredoc(char *del)
{
	pid_t	child;

	child = fork();
	if (child == -1)
		return (perror(NAME), false);
	if (child == 0)
	{
		sigaction(SIGINT, &(struct sigaction){.sa_handler = SIG_DFL}, NULL);
		open_heredoc(del);
	}
	wait(NULL);
	return (true);
}
