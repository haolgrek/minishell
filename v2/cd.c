/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 03:10:03 by rluder            #+#    #+#             */
/*   Updated: 2017/05/15 18:25:01 by rluder           ###   ########.fr       */
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
			free(tchar);
		}
		if (tmp[0])
			free(tmp[0]);
		if (tmp[1])
			free(tmp[1]);
		if (tmp)
			free(tmp);
		varenv = varenv->next;
	}
	if (buf)
		free(buf);
}

void			chdir_slash(char **args, t_varenv *start)
{
	DIR			*dir;

	dir = opendir(args[1]);
	if (dir)
	{
		chdir(args[1]);
		new_pwd(args[1], start);
		closedir(dir);
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
	DIR		*dir;

	tmp = ft_strjoin(pwd, "/");
	tmp2 = ft_strjoin(tmp, args[1]);
	dir = opendir(tmp2);
	if (dir)
	{
		chdir(tmp2);
		new_pwd(tmp2, start);
		closedir(dir);
	}
	else
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(args[1]);
	}
	if (tmp)
		free(tmp);
	if (tmp2)
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
			pwd = ft_memalloc(ft_strlen(tmp[1]) + 1);
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
	if (args[1][0] == '/')
		chdir_slash(args, start);
	else
		chdir_new(pwd, args, start);
	if (pwd)
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
