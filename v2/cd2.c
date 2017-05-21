/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 03:22:19 by rluder            #+#    #+#             */
/*   Updated: 2017/05/21 21:02:33 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			homeispwd(char *home, t_varenv *varenv)
{
	char		**tmp;
	char		*temp;

	tmp = NULL;
	temp = NULL;
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

void			do_home(char *home, t_varenv *varenv)
{
	if (home)
	{
		homeispwd(home, varenv);
		if (access(home, F_OK))
			errorhome(home);
	}
}

void			copypwd(char *oldpwd, t_varenv *varenv)
{
	char		*tchar;

	tchar = ft_strjoin("PWD=", oldpwd);
	varenv->var = ft_strcpy(varenv->var, tchar);
	free(tchar);
}

void			copyoldpwd(char *pwd, t_varenv *varenv)
{
	char		*tchar;

	tchar = ft_strjoin("OLDPWD=", pwd);
	varenv->var = ft_strcpy(varenv->var, tchar);
	free(tchar);
}

void			revert_pwd(t_varenv *varenv)
{
	char		*pwd;
	char		*oldpwd;
	t_varenv	*start;
	char		**tmp;

	start = varenv;
	pwd = ft_memalloc(256);
	oldpwd = ft_memalloc(256);
	tmp = NULL;
	revertwhile1(start, pwd);
	revertwhile2(start, oldpwd);
	while (varenv)
	{
		tmp = ft_strsplit(varenv->var, '=');
		if (!ft_strcmp("PWD", tmp[0]) && !access(oldpwd, F_OK))
			copypwd(oldpwd, varenv);
		if (!ft_strcmp("OLDPWD", tmp[0]))
			copyoldpwd(pwd, varenv);
		varenv = varenv->next;
		letsfree(tmp);
	}
	chdir(oldpwd);
	varenv = start;
	freechars(pwd);
	freechars(oldpwd);
}
