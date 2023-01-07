/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:54:09 by hjabbour          #+#    #+#             */
/*   Updated: 2022/10/25 11:46:54 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

void	free_env(t_var	*env)
{
	t_var	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->str);
		free(tmp);
	}
}

static void	append_rest(char **env, t_var *head)
{
	int	idx;

	idx = 0;
	while (env && env[idx])
	{
		if (ft_strncmp(env[idx], "OLDPWD=", 7)
			&& ft_strncmp(env[idx], "PWD=", 4) && ft_strncmp(env[idx], "_=", 2)
			&& ft_strncmp(env[idx], "SHLVL=", 6))
		{
			blt_export((char *[]){env[idx], NULL}, head);
		}
		idx++;
	}
}

t_var	*env_dup(char **env)
{
	t_var		*head;
	t_var		*node;
	char *const	buff = getcwd((char [PATH_MAX]){0}, PATH_MAX);

	head = list_create(4);
	if (!head)
		exit(EXIT_FAILURE);
	node = head;
	node->str = ft_strdup("_=/usr/bin/env");
	node = node->next;
	node->str = ft_strjoin("PWD=", buff);
	node = node->next;
	node->str = ft_strdup("OLDPWD");
	node = node->next;
	node->str = get_shlvl();
	node = node->next;
	node->str = ft_strjoin("PATH=", _PATH_STDPATH);
	node->next = NULL;
	append_rest(env, head);
	return (head);
}
