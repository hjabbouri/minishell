/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:57:15 by stamim            #+#    #+#             */
/*   Updated: 2022/10/25 12:59:31 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>

char	g_s[4] = "0";

static void	quit(t_var *env, const int status)
{
	clear_history();
	free_env(env);
	exit(status);
}

int	main(int _ac, char **restrict _av, char **envp)
{
	t_pipln			pip;
	t_token			*tkns;
	char			*inp;
	t_var *const	env = env_dup(envp);

	rl_catch_signals = false;
	sigaction(SIGINT, &(struct sigaction){.sa_handler = nw_prmpt}, NULL);
	sigaction(SIGQUIT, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
	inp = readline(PROMPT);
	while (rl_replace_line("", 0), inp)
	{
		tkns = lex(inp, env);
		free(inp);
		if (tkns)
		{
			pip = (t_pipln){0, .pid = -2, .e = env, .tty = {dup(0), dup(1)}};
			if (pip.tty[0] == -1 || pip.tty[1] == -1)
				(perror(NAME), ft_lst_del_all(tkns), quit(env, EXIT_FAILURE));
			ft_itoa(g_s, lst_pipe(pip, tkns));
			if (dup2(pip.tty[0], 0) == -1 || dup2(pip.tty[1], 1) == -1)
				(perror(NAME), quit(env, EXIT_FAILURE));
		}
		inp = readline(PROMPT);
	}
	quit(env, ((void)_ac, (void)_av, EXIT_SUCCESS));
}
