/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:26:00 by stamim            #+#    #+#             */
/*   Updated: 2022/10/25 12:01:02 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

void	deallocate_node_env(t_var *env)
{
	free(env->str);
	free(env);
}

t_var	*ft_new_node_env(char *str)
{
	t_var	*node;

	node = ft_malloc(sizeof(t_var));
	if (!node)
		return (NULL);
	node->str = str;
	node->next = NULL;
	return (node);
}

void	ft_env_push_back(t_var *head, t_var *new)
{
	while (head->next)
		head = head->next;
	head->next = new;
}

bool	compare(const char *key, const char *cmp)
{
	size_t	idx;

	idx = 0;
	if (!key || !cmp)
		return (false);
	while (cmp[idx] && cmp[idx] != '=' && key[idx])
	{
		if (key[idx] != cmp[idx])
			return (false);
		idx++;
	}
	if (!key[idx])
		return (!cmp[idx] || cmp[idx] == '=');
	return (key[idx] == '=');
}

char	**list2arr(t_var *env)
{
	size_t	sze;
	t_var	*tmp;
	t_var	*to_free;
	char	**args;

	sze = 0;
	tmp = env;
	while (tmp && ++sze)
		tmp = tmp->next;
	args = ft_malloc(sizeof(char *) * (sze + 1));
	if (!args)
		exit(EXIT_FAILURE);
	args[sze] = NULL;
	tmp = env;
	sze = 0;
	while (tmp)
	{
		args[sze++] = tmp->str;
		to_free = tmp;
		tmp = tmp->next;
		free(to_free);
	}
	return (args);
}
