/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:04:05 by hjabbour          #+#    #+#             */
/*   Updated: 2022/10/25 11:53:25 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

static void	env_update(t_var *env, char *pwd)
{
	char *const	new_pwd = getcwd((char [PATH_MAX]){0}, PATH_MAX);
	t_var		*tmp;
	t_var		*tmp_old;

	if (!pwd)
		pwd = "";
	tmp_old = get_env_node("OLDPWD", env);
	if (!tmp_old)
	{
		tmp_old = ft_new_node_env(ft_strjoin("OLDPWD=", pwd));
		ft_env_push_back(env, tmp_old);
	}
	if (tmp_old)
		tmp_old->str = (free(tmp_old->str), ft_strjoin("OLDPWD=", pwd));
	tmp = get_env_node("PWD=", env);
	if (!tmp)
	{
		tmp = ft_new_node_env(ft_strjoin("PWD=", new_pwd));
		ft_env_push_back(env, tmp);
	}
	if (tmp)
		tmp->str = (free(tmp->str), ft_strjoin("PWD=", new_pwd));
}

static int	ft_cwd(char *dir, t_var *env, char *msg)
{
	int		ret;
	char	*set;

	set = ft_getenv(dir, env);
	if (!set || !set[0])
		return (ft_perror(CD_NAME, msg, NULL), -1);
	ret = chdir(set);
	if (ret == -1)
		return (perror(CD_NAME), -1);
	return (1);
}

int	blt_cd(char *args[], t_var *env)
{
	int			ret;
	char *const	pwd = getcwd((char [PATH_MAX]){0}, PATH_MAX);

	if (!args[0])
	{
		ret = ft_cwd("HOME=", env, HOME_MISS);
		if (ret == -1)
			return (EXIT_FAILURE);
	}
	else if (!args[0][0] && !args[1])
		return (EXIT_SUCCESS);
	else if (args[0] && args[1])
		return (ft_perror(CD_NAME, MULTI_ARG, NULL), (errno << 8));
	else if (args[0][0] == '-' && !args[0][1])
	{
		ret = ft_cwd("OLDPWD", env, OLDPWD_MISS);
		if (ret == -1)
			return (EXIT_FAILURE);
		printf("%s\n", ft_getenv("OLDPWD=", env));
	}
	else
		ret = chdir(args[0]);
	if (ret == -1)
		return (ft_perror(CD_NAME, args[0], FILE_DIR_MISS), EXIT_FAILURE);
	return (env_update(env, pwd), EXIT_SUCCESS);
}
