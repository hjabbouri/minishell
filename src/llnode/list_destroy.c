/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stamim <stamim@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:33:27 by stamim            #+#    #+#             */
/*   Updated: 2022/10/18 08:38:24 by stamim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"
#include <stdlib.h>

void	ft_lst_del_one(t_token *tkn)
{
	if (tkn && tkn->type == WORD)
		free((void *)tkn->wrd);
	free(tkn);
}

void	ft_lst_del_all(t_token *tkn)
{
	t_token	*tmp;

	while (tkn)
	{
		tmp = tkn;
		tkn = tkn->next;
		ft_lst_del_one(tmp);
	}
}
