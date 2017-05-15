/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unpack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 02:59:07 by rluder            #+#    #+#             */
/*   Updated: 2017/05/15 18:32:20 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**unpack_path(t_varenv *varenv)
{
	char		*unpack;
	char		**path;
	char		**tmp;

	unpack = malloc(sizeof(char) * 255);
	while (varenv)
	{
		tmp = ft_strsplit(varenv->var, '=');
		if (!ft_strcmp("PATH", tmp[0]))
			unpack = ft_strcpy(unpack, tmp[1]);
		if (tmp[0])
			free(tmp[0]);
		if (tmp[1])
			free(tmp[1]);
		if (tmp)
			free(tmp);
		varenv = varenv->next;
	}
	path = ft_strsplit(unpack, ':');
	if (unpack)
		free(unpack);
	return (path);
}

char			*unpack_pwd(t_varenv *varenv)
{
	char		*pwd;
	char		**tmp;

	while (varenv)
	{
		tmp = ft_strsplit(varenv->var, '=');
		if (!ft_strcmp("PWD", tmp[0]))
		{
			pwd = malloc(sizeof(char) * (ft_strlen(varenv->var) - 4));
			pwd = ft_strcpy(pwd, tmp[1]);
		}
		if (tmp[0])
			free(tmp[0]);
		if (tmp[1])
			free(tmp[1]);
		if (tmp)
			free(tmp);
		varenv = varenv->next;
	}
	return (pwd);
}

char			**redo_env(t_varenv *varenv)
{
	t_varenv	*start;
	int			i;
	int			j;
	char		**env;

	j = 0;
	start = varenv;
	while (varenv)
	{
		j++;
		varenv = varenv->next;
	}
	varenv = start;
	env = malloc(sizeof(char *) * (j + 1));
	i = 0;
	while (i < j)
	{
		env[i] = malloc(sizeof(char) * ft_strlen(varenv->var));
		env[i] = ft_strcpy(env[i], varenv->var);
		i++;
	}
	env[i] = NULL;
	return (env);
}
