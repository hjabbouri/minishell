/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stamim <stamim@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:47:37 by stamim            #+#    #+#             */
/*   Updated: 2022/10/18 11:40:38 by stamim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void	ft_push_front(t_token **head, t_token *new)
{
	new->next = *head;
	*head = new;
}

t_token	*ft_new_node(char *wrd, size_t opr, size_t typ)
{
	t_token *const	node = ft_malloc(sizeof(t_token));

	if (node)
	{
		node->wrd = wrd;
		node->opr = opr;
		node->type = typ;
		node->next = NULL;
	}
	return (node);
}

t_token	*ft_pop_front(t_token **head)
{
	t_token	*first;

	first = NULL;
	if (head && *head)
	{
		first = *head;
		*head = first->next;
		first->next = NULL;
	}
	return (first);
}

void	ft_push_back(t_token **head, t_token *new)
{
	t_token	*node;

	if (*head)
	{
		node = *head;
		while (node->next)
			node = node->next;
		node->next = new;
	}
	else
		*head = new;
}

t_token	*ft_pop_back(t_token **head)
{
	t_token	*last;
	t_token	*node;

	last = NULL;
	if (head && *head)
	{
		node = *head;
		if (!node->next)
		{
			last = node;
			*head = NULL;
		}
		else
		{
			while (node->next->next)
				node = node->next;
			last = node->next;
			node->next = NULL;
		}
	}
	return (last);
}
