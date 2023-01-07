/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:51:56 by hjabbour          #+#    #+#             */
/*   Updated: 2022/10/25 12:01:25 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

static void	del_all_var(t_var *head)
{
	t_var	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

t_var	*list_create(size_t sze)
{
	t_var	*node;
	t_var	*next;
	t_var	*head;

	if (!sze)
		return (NULL);
	head = ft_malloc(sizeof(t_var));
	if (!head)
		return (NULL);
	node = head;
	while (sze--)
	{
		next = ft_malloc(sizeof(t_var));
		if (!next)
			return (del_all_var(head), NULL);
		node->next = next;
		node = next;
	}
	return (head);
}
