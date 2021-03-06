/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 03:22:19 by rluder            #+#    #+#             */
/*   Updated: 2017/05/10 18:59:22 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			homeispwd(char *home, t_varenv *varenv)
{
	while (varenv)
	{
		if (!ft_strcmp("PWD", ft_strsplit(varenv->var, '=')[0]) &&
				!access(home, F_OK))
		{
			varenv->var = ft_strjoin("PWD=", home);
			chdir(home);
		}
		varenv = varenv->next;
	}
}

void			go_pwd(t_varenv *varenv)
{
	t_varenv	*var1;
	char		*home;

	var1 = varenv;
	home = malloc(sizeof(char) * 256);
	while (varenv)
	{
		if (!ft_strcmp("HOME", ft_strsplit(varenv->var, '=')[0]))
		{
			if (ft_strlen(ft_strsplit(varenv->var, '=')[1]) < 256)
				home = ft_strcpy(home, ft_strsplit(varenv->var, '=')[1]);
			else
				ft_putendl("Path too long");
		}
		varenv = varenv->next;
	}
	varenv = var1;
	homeispwd(home, varenv);
	if (access(home, F_OK))
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(home);
	}
	varenv = var1;
	free(home);
}

void			revertwhile1(t_varenv *varenv, char *pwd)
{
	while (varenv)
	{
		if (!ft_strcmp("PWD", ft_strsplit(varenv->var, '=')[0]))
			pwd = ft_strcpy(pwd, ft_strsplit(varenv->var, '=')[1]);
		varenv = varenv->next;
	}
}

void			revertwhile2(t_varenv *varenv, char *oldpwd)
{
	while (varenv)
	{
		if (!ft_strcmp("OLDPWD", ft_strsplit(varenv->var, '=')[0]))
			oldpwd = ft_strcpy(oldpwd, ft_strsplit(varenv->var, '=')[1]);
		varenv = varenv->next;
	}
}

void			revert_pwd(t_varenv *varenv)
{
	char		*pwd;
	char		*oldpwd;
	t_varenv	*start;

	start = varenv;
	pwd = malloc(sizeof(char) * 256);
	oldpwd = malloc(sizeof(char) * 256);
	revertwhile1(varenv, pwd);
	varenv = start;
	revertwhile2(varenv, oldpwd);
	varenv = start;
	while (varenv)
	{
		if (!ft_strcmp("PWD", ft_strsplit(varenv->var, '=')[0])
				&& !access(oldpwd, F_OK))
			varenv->var = ft_strcpy(varenv->var, ft_strjoin("PWD=", oldpwd));
		if (!ft_strcmp("OLDPWD", ft_strsplit(varenv->var, '=')[0]))
			varenv->var = ft_strcpy(varenv->var, ft_strjoin("OLDPWD=", pwd));
		varenv = varenv->next;
	}
	chdir(oldpwd);
	varenv = start;
	free(pwd);
	free(oldpwd);
}
