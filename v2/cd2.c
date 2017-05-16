/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 03:22:19 by rluder            #+#    #+#             */
/*   Updated: 2017/05/16 17:48:20 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			homeispwd(char *home, t_varenv *varenv)
{
	char		**tmp;
	char		*temp;

	while (varenv)
	{
		tmp = ft_strsplit(varenv->var, '=');
		if (!ft_strcmp("PWD", tmp[0]) && !access(home, F_OK))
		{
			temp = ft_strjoin("PWD=", home);
			varenv->var = ft_strcpy(varenv->var, temp);
			chdir(home);
			if (tmp)
				free(temp);
		}
		letsfree(tmp);
		varenv = varenv->next;
	}
}

void			go_pwd(t_varenv *varenv)
{
	t_varenv	*var1;
	char		*home;
	char		**tmp;

	var1 = varenv;
	while (varenv)
	{
		tmp = ft_strsplit(varenv->var, '=');
		if (!ft_strcmp("HOME", tmp[0]))
		{
			if (ft_strlen(tmp[1]) < 256)
			{
				home = ft_memalloc(ft_strlen(tmp[1]) + 1);
				home = ft_strcpy(home, tmp[1]);
			}
		}
		letsfree(tmp);
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
	if (home)
		free(home);
}

void			revertwhile1(t_varenv *varenv, char *pwd)
{
	char	**tmp;

	while (varenv)
	{
		tmp = ft_strsplit(varenv->var, '=');
		if (!ft_strcmp("PWD", tmp[0]))
			pwd = ft_strcpy(pwd, tmp[1]);
		letsfree(tmp);
		varenv = varenv->next;
	}
}

void			revertwhile2(t_varenv *varenv, char *oldpwd)
{
	char	**tmp;

	while (varenv)
	{
		tmp = ft_strsplit(varenv->var, '=');
		if (!ft_strcmp("OLDPWD", tmp[0]))
			oldpwd = ft_strcpy(oldpwd, tmp[1]);
		letsfree(tmp);
		varenv = varenv->next;
	}
}

void			revert_pwd(t_varenv *varenv)
{
	char		*pwd;
	char		*oldpwd;
	t_varenv	*start;
	char		**tmp;
	char		*tchar;
	char		*tchar2;

	start = varenv;
	pwd = ft_memalloc(256);
	oldpwd = ft_memalloc(256);
	revertwhile1(varenv, pwd);
	varenv = start;
	revertwhile2(varenv, oldpwd);
	varenv = start;
	while (varenv)
	{
		tmp = ft_strsplit(varenv->var, '=');
		if (!ft_strcmp("PWD", tmp[0])
				&& !access(oldpwd, F_OK))
		{
			tchar = ft_strjoin("PWD=", oldpwd);
			varenv->var = ft_strcpy(varenv->var, tchar);
			free(tchar);
		}
		if (!ft_strcmp("OLDPWD", tmp[0]))
		{
			tchar2 = ft_strjoin("OLDPWD=", pwd);
			varenv->var = ft_strcpy(varenv->var, tchar2);
			free(tchar2);
		}
		varenv = varenv->next;
		letsfree(tmp);
	}
	chdir(oldpwd);
	varenv = start;
	if (pwd)
		free(pwd);
	if (oldpwd)
		free(oldpwd);
}
