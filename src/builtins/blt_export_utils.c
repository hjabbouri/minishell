/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:54:47 by hjabbour          #+#    #+#             */
/*   Updated: 2022/10/25 12:37:45 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

static void	blt_ft_strlcpy(char	*dst, const char *src, const int idx, int count)
{
	int	end;

	end = idx;
	if (end > 0)
	{
		while (src[count] != '\0' && count < end)
		{
			dst[count] = src[count];
			count++;
		}
		if (count == (int)ft_strlen(src))
			dst[count] = '\0';
	}
	count++;
	end = (int)ft_strlen(src);
	if (end > 0)
	{
		while (src[count] != '\0' && count < end)
		{
			dst[count - 1] = src[count];
			count++;
		}
		if (count == (int)ft_strlen(src))
			dst[count - 1] = '\0';
	}
}

int	export_add_back_env(char *str, int idx, t_var *env)
{
	t_var	*new;
	char	*join;

	join = NULL;
	new = ft_malloc(sizeof(t_var));
	if (!new)
		return (EXIT_FAILURE);
	if (idx != -1)
	{
		blt_ft_strlcpy(join = malloc(sizeof(char) * (int)ft_strlen(str) - 1),
			str, idx, 0);
		new->str = ft_strdup(join);
	}
	else
		new->str = ft_strdup(str);
	new->next = NULL;
	ft_env_push_back(env, new);
	return (free(join), EXIT_SUCCESS);
}

int	join_var_env(char *src, int idx, t_var *env)
{
	t_var	*tmp;
	char	*str;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->str, src, idx) == 0)
		{
			str = ft_strjoin(tmp->str, src + idx + 1
					+ (src[idx] == '=' || tmp->str[idx] == '='));
			free(tmp->str);
			tmp->str = str;
			return (EXIT_SUCCESS);
		}
		tmp = tmp->next;
	}
	return (EXIT_FAILURE);
}

int	replace_var_env(char *str, int idx, t_var *env)
{
	t_var	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->str, str, idx))
		{
			free(tmp->str);
			tmp->str = ft_strdup(str);
			return (EXIT_SUCCESS);
		}
		tmp = tmp->next;
	}
	return (EXIT_FAILURE);
}

bool	check_exist_var_env(char *str, int idx, t_var *env)
{
	t_var	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->str, str, idx))
			return (true);
		tmp = tmp->next;
	}
	return (false);
}
