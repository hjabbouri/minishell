/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:50:47 by hjabbour          #+#    #+#             */
/*   Updated: 2022/10/25 12:54:37 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void	nw_prmpt(int _siginfo)
{
	rl_replace_line("", 0);
	write(0, "\n", 1);
	if (wait(NULL) == -1)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	ft_itoa(g_s, 128 + _siginfo);
}

void	reset_signals(void)
{
	sigaction(SIGINT, &(struct sigaction){.sa_handler = SIG_DFL}, NULL);
	sigaction(SIGQUIT, &(struct sigaction){.sa_handler = SIG_DFL}, NULL);
}
