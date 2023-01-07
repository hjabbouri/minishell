/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:10:41 by stamim            #+#    #+#             */
/*   Updated: 2022/10/25 12:55:25 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"
#include <stdio.h>
#include <stdlib.h>

bool	spec(const char *input)
{
	return (*input == '>' || *input == '<' || *input == '|');
}

bool	blank(const char chr)
{
	return (chr == ' ' || chr == '\t');
}

static int	get_oper(char **inp)
{
	if (**inp == '<')
	{
		if (*++*inp == '<')
			return (*inp += 1, HEREDOC);
		return (IN);
	}
	if (**inp == '>')
	{
		if (*++*inp == '>')
			return (*inp += 1, OUT_APND);
		return (OUT);
	}
	return (*inp += 1, PIPE);
}

static t_token	*yield_next_token(char **inp, t_var *g_env)
{
	t_token *const	tkn = ft_new_node(0, 0, OPERATOR);

	if (!tkn)
		return (free(*inp), *inp = NULL, NULL);
	while (blank(**inp))
		*inp += 1;
	if (!**inp)
		return (free(tkn), NULL);
	if (spec(*inp))
	{
		tkn->opr = get_oper(inp);
		return (tkn);
	}
	tkn->type = WORD;
	tkn->wrd = (char *)get_word(inp, g_env);
	if (!tkn->wrd)
		return (free(tkn), NULL);
	return (tkn);
}

t_token	*lex(char *inp, t_var *g_env)
{
	t_token	*lst;
	t_token	*nxt;

	if (*inp)
		add_history(inp);
	lst = yield_next_token(&inp, g_env);
	nxt = lst;
	while (nxt && inp)
	{
		nxt->next = yield_next_token(&inp, g_env);
		if (nxt->type == OPERATOR && nxt->opr == PIPE && (!nxt->next
				|| (nxt->next->type == OPERATOR && nxt->next->opr == PIPE)))
			return (ft_perror(OPR, 0, 0), ft_lst_del_all(lst), NULL);
		if (nxt->type == OPERATOR && nxt->opr != PIPE)
		{
			if (!nxt->next || nxt->next->type != WORD)
				return (ft_perror(OPR, 0, 0), ft_lst_del_all(lst), NULL);
			if (nxt->opr == HEREDOC && !heredoc(nxt->next->wrd))
				return (ft_lst_del_all(lst), NULL);
		}
		nxt = nxt->next;
	}
	if (!inp)
		return (ft_lst_del_all(lst), NULL);
	return (lst);
}
