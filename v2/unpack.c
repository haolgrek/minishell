/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unpack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 02:59:07 by rluder            #+#    #+#             */
/*   Updated: 2017/05/21 18:58:38 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*do_unpack(char *unpack, char *tmp)
{
	unpack = ft_strcpy(unpack, tmp);
	return (unpack);
}

void			set_null(char ***path, char ***tmp)
{
	*path = NULL;
	*tmp = NULL;
}

char			**unpack_path(t_varenv *varenv)
{
	char		*unpack;
	char		**path;
	char		**tmp;

	set_null(&path, &tmp);
	unpack = NULL;
	while (varenv)
	{
		tmp = ft_strsplit(varenv->var, '=');
		if (tmp && tmp[0] && tmp[1])
		{
			if (!ft_strcmp("PATH", tmp[0]))
			{
				unpack = ft_memalloc(sizeof(char) * (ft_strlen(tmp[1]) + 1));
				unpack = do_unpack(unpack, tmp[1]);
			}
		}
		ft_free_strsplit(tmp);
		varenv = varenv->next;
	}
	if (unpack)
		path = ft_strsplit(unpack, ':');
	freechars(unpack);
	return (path);
}

char			*unpack_pwd(t_varenv *varenv)
{
	char		*pwd;
	char		**tmp;

	pwd = NULL;
	tmp = NULL;
	while (varenv)
	{
		tmp = ft_strsplit(varenv->var, '=');
		if (tmp && tmp[0] && tmp[1])
		{
			if (!ft_strcmp("PWD", tmp[0]))
			{
				if (tmp[1])
				{
					pwd = ft_memalloc(ft_strlen(tmp[1]) + 1);
					pwd = ft_strcpy(pwd, tmp[1]);
				}
				else
					return (NULL);
			}
		}
		ft_free_strsplit(tmp);
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
	env = NULL;
	start = varenv;
	while (varenv)
	{
		j++;
		varenv = varenv->next;
	}
	varenv = start;
	env = ft_memalloc(sizeof(char*) * (j + 1));
	i = 0;
	while (i < j)
	{
		env[i] = ft_memalloc(ft_strlen(varenv->var) + 1);
		env[i] = ft_strcpy(env[i], varenv->var);
		varenv = varenv->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}
