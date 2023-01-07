/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:58:48 by hjabbour          #+#    #+#             */
/*   Updated: 2022/10/22 16:08:07 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"
#include <stdlib.h>

static size_t	max_len(char *str1, char *str2)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 <= len2)
		len1 = 0;
	else
		len2 = 0;
	return (len1 + len2);
}

static	void	sort(t_var *env)
{
	t_var	*tmp;
	char	*str;

	tmp = env->next;
	while (tmp && tmp->next)
	{
		if (ft_strncmp(tmp->str, tmp->next->str,
				max_len(tmp->str, tmp->next->str)) > 0)
		{
			str = tmp->str;
			tmp->str = tmp->next->str;
			tmp->next->str = str;
			tmp = env->next;
			continue ;
		}
		tmp = tmp->next;
	}
}

static	int	print(t_var *env)
{
	t_var	*tmp;
	char	*str;

	sort(env);
	str = NULL;
	tmp = env->next;
	while (tmp)
	{
		write(STDOUT_FILENO, EXPRT_PRE, sizeof(EXPRT_PRE));
		write(STDOUT_FILENO, tmp->str, ft_chr(tmp->str, '=', 0));
		str = ft_strchr(tmp->str, '=');
		if (str)
			printf("=\"%s\"\n", str + 1);
		else
			printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

static	int	add_value(char *str, t_var *env)
{
	int		idx;

	idx = 0;
	if (!str)
		return (EXIT_FAILURE);
	while (str[idx] && str[idx] != '=' && str[idx] != '+')
	{
		if (!ft_isalnum(str[idx]) && str[idx] != '_')
			return (ft_perror(EXP_TIT, str, EXP_IDE), EXIT_FAILURE);
		idx++;
	}
	if (str[idx] == '+' && (!str[idx + 1] || str[idx + 1] != '='))
		return (ft_perror(EXP_TIT, str, EXP_IDE), EXIT_FAILURE);
	if (check_exist_var_env(str, idx, env))
	{
		if (str[idx] == '+' && str[idx + 1] == '=')
			return (join_var_env(str, idx, env));
		return (replace_var_env(str, idx, env));
	}
	if (str[idx] && str[idx + 1] && str[idx] == '+' && str[idx + 1] == '=')
		return (export_add_back_env(str, idx, env));
	return (export_add_back_env(str, -1, env));
}

int	blt_export(char *args[], t_var *env)
{
	int	status;
	int	idx;

	status = EXIT_SUCCESS;
	idx = 0;
	if (!args || !env)
		return (EXIT_FAILURE);
	if (!args[idx])
		return (print(env));
	while (args[idx])
	{
		if (ft_isdigit(args[idx][0]))
			status = (ft_perror(EXP_TIT, args[idx], EXP_IDE),
					EXIT_FAILURE);
		else
			status = add_value(args[idx], env);
		idx++;
	}
	return (status);
}
