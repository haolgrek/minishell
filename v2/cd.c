/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 03:10:03 by rluder            #+#    #+#             */
/*   Updated: 2017/05/14 20:33:04 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			new_pwd(char *arg, t_varenv *varenv)
{
	t_varenv	*start;
	char		*buf;
	char		*cwd;
	char		**tmp;
	char		*tchar;

	buf = malloc(sizeof(char*) * 256);
	cwd = getcwd(buf, 255);
	start = varenv;
	while (varenv)
	{
		tmp = ft_strsplit(varenv->var, '=');
		if (!ft_strcmp("PWD", tmp[0]))
		{
			tchar = ft_strjoin("PWD=", cwd);
			varenv->var = ft_strcpy(varenv->var, tchar);
		}
		if (tmp[0])
			free(tmp[0]);
		if (tmp[1])
			free(tmp[1]);
		free(tmp);
		varenv = varenv->next;
	}
	free(buf);
}

void			chdir_slash(char **args, t_varenv *start)
{
	if (opendir(args[1]))
	{
		chdir(args[1]);
		new_pwd(args[1], start);
	}
	else
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(args[1]);
		return ;
	}
}

void			chdir_new(char *pwd, char **args, t_varenv *start)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(pwd, "/");
	tmp2 = ft_strjoin(tmp, args[1]);
	if (opendir(tmp2))
	{
		chdir(tmp2);
		new_pwd(tmp2, start);
	}
	else
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(args[1]);
	}
	free(tmp);
	free(tmp2);
}

void			change_dir(char **args, t_varenv *varenv)
{
	char		*pwd;
	t_varenv	*start;
	char		**tmp;

	start = varenv;
	if (args[2])
	{
		ft_putstr("cd: string not in pwd: ");
		ft_putendl(args[2]);
		return ;
	}
	while (varenv)
	{
		tmp = ft_strsplit(varenv->var, '=');
		if (!ft_strcmp("PWD", tmp[0]))
		{
			pwd = malloc(sizeof(char*) * (ft_strlen(varenv->var) - 4));
			pwd = ft_strcpy(pwd, tmp[1]);
		}
		if (tmp[0])
			free(tmp[0]);
		if (tmp[1])
			free(tmp[1]);
		free(tmp);
		varenv = varenv->next;
	}
	if (args[1][0] == '/')
		chdir_slash(args, start);
	else
		chdir_new(pwd, args, start);
	free(pwd);
}

void			do_cd(char **args, t_varenv *varenv)
{
	if (!args[1])
		go_pwd(varenv);
	else if (!ft_strcmp(args[1], "-"))
		revert_pwd(varenv);
	else
		change_dir(args, varenv);
}
