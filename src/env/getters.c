/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:07:34 by stamim            #+#    #+#             */
/*   Updated: 2022/10/25 11:56:08 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

static size_t	number_digits(size_t num)
{
	u_char	digits;

	digits = 1;
	while (num / BASE)
	{
		num /= BASE;
		digits += 1;
	}
	return (digits);
}

char	*get_shlvl(void)
{
	char	*val;
	char	*buff;
	char	*join;
	size_t	lvl;
	size_t	sze;

	lvl = 0;
	val = getenv(SHLVL);
	if (!val)
		return (ft_strjoin(SHLVL"=", "1"));
	while (*val)
		lvl = (lvl * BASE) + (*val++ - '0');
	lvl += 1;
	sze = number_digits(lvl);
	buff = ft_malloc(sze + 1);
	join = ft_strjoin(SHLVL"=", ft_itoa(buff, (int)lvl));
	free(buff);
	return (join);
}

t_var	*get_env_node(char *key, t_var *env)
{
	t_var	*tmp;

	if (!env)
		return (NULL);
	tmp = env;
	while (tmp && !compare(key, tmp->str))
		tmp = tmp->next;
	return (tmp);
}

char	*ft_getenv(const char *key, t_var *env)
{
	if (!env)
		return (NULL);
	if (key && *key && *key == '?')
		return (g_s);
	while (env)
	{
		if (compare(key, env->str))
			break ;
		env = env->next;
	}
	if (!env || !env->str)
		return (NULL);
	if (!ft_chr(env->str, '=', 0))
		return ("");
	return (env->str + ft_chr(env->str, '=', 0) + 1);
}
