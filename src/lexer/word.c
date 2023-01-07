/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 10:57:47 by stamim            #+#    #+#             */
/*   Updated: 2022/10/25 12:30:50 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static const char	*s_quo(char **input)
{
	const char	*str = *input;

	while (*++*input != '\'')
		if (!**input)
			return (write(STDERR_FILENO, QUO_MISMATCH, sizeof(QUO_MISMATCH)),
				*input = NULL, NULL);
	**input = '\0';
	*input += 1;
	return (str + 1);
}

static const char	*env(char **inp, t_var *g_env, const bool quo)
{
	const char	*key = *inp;
	const char	*val = "";

	while ((*inp)[1] && (*inp)[1] != '$' && (*inp)[1] != '=' && (*inp)[1] != '+'
		&& (*inp)[1] != '\'' && (*inp)[1] != '"'
			&& !blank((*inp)[1]) && !spec(*inp + 1))
	{
		*inp += 1;
		if (**inp == '?')
			break ;
	}
	if (key == *inp)
		val = "$";
	else
	{
		val = ft_getenv((key = ft_strndup(key + 1, *inp - key)), g_env);
		free((void *)key);
	}
	if (!quo)
		*inp += 1;
	return (val);
}

static const char	*d_quo(char **inpt, t_var *g_env)
{
	const char	*str = ft_strdup("");
	const char	*tmp;

	while (str && *++*inpt != '"')
	{
		if (!**inpt)
			return (write(STDERR_FILENO, QUO_MISMATCH,
					sizeof(QUO_MISMATCH)), free((void *)str),
				*inpt = NULL, NULL);
		tmp = str;
		if (**inpt == '$')
			str = ft_strjoin(str, env(inpt, g_env, true));
		else
			str = ft_strjoin(str, (char [2]){**inpt, '\0'});
		free((void *)tmp);
	}
	return (*inpt += 1, str);
}

const char	*get_word(char **inp, t_var *g_env)
{
	const char	*pt1;
	const char	*pt2;
	const char	*wrd = ft_strdup("");

	while (wrd && **inp && !blank(**inp) && !spec(*inp))
	{
		pt1 = wrd;
		if (**inp == '$')
			wrd = ft_strjoin(pt1, env(inp, g_env, false));
		else if (**inp == '\'')
			wrd = ft_strjoin(pt1, s_quo(inp));
		else if (**inp == '"')
		{
			wrd = ft_strjoin(pt1, pt2 = d_quo(inp, g_env));
			free((void *)pt2);
		}
		else
			wrd = ft_strjoin(wrd, (char [2]){*(*inp)++, '\0'});
		free((void *)pt1);
	}
	return (wrd);
}
