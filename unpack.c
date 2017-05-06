/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unpack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 02:59:07 by rluder            #+#    #+#             */
/*   Updated: 2017/05/06 03:08:00 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**unpack_path(t_varenv *varenv)
{
	char		*unpack;
	char		**path;

	unpack = malloc(sizeof(char) * 255);
	while (varenv)
	{
		if (!ft_strcmp("PATH", ft_strsplit(varenv->var, '=')[0]))
			unpack = ft_strcpy(unpack, ft_strsplit(varenv->var, '=')[1]);
		varenv = varenv->next;
	}
	path = ft_strsplit(unpack, ':');
	free(unpack);
	return (path);
}

char			*unpack_pwd(t_varenv *varenv)
{
	char		*pwd;

	pwd = malloc(sizeof(char) * 255);
	while (varenv)
	{
		if (!ft_strcmp("PWD", ft_strsplit(varenv->var, '=')[0]))
			pwd = ft_strcpy(pwd, ft_strsplit(varenv->var, '=')[1]);
		varenv = varenv->next;
	}
	return (pwd);
}

char			**redo_env(t_varenv *varenv)
{
	t_varenv	*start;
	int			i;
	char		**env;

	i = 0;
	start = varenv;
	while (varenv)
	{
		i++;
		varenv = varenv->next;
	}
	varenv = start;
	env = malloc(sizeof(char *) * i);
	i = 0;
	while (env[i])
	{
		env[i] = ft_strcpy(env[i], varenv->var);
		i++;
	}
	return (env);
}
