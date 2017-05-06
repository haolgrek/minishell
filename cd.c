/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 03:10:03 by rluder            #+#    #+#             */
/*   Updated: 2017/05/06 03:19:03 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			new_pwd(char *arg, t_varenv *varenv)
{
	t_varenv	*start;
	char		*buf;
	char		*cwd;

	buf = malloc(sizeof(char) * 256);
	cwd = getcwd(buf, 255);
	start = varenv;
	while (varenv)
	{
		if (!ft_strcmp("PWD", ft_strsplit(varenv->var, '=')[0]))
			varenv->var = ft_strcpy(varenv->var, ft_strjoin("PWD=", cwd));
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
	if (opendir(ft_strjoin(ft_strjoin(pwd, "/"), args[1])))
	{
		chdir(ft_strjoin(ft_strjoin(pwd, "/"), args[1]));
		new_pwd(ft_strjoin(ft_strjoin(pwd, "/"), args[1]), start);
	}
	else
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(args[1]);
	}
}

void			change_dir(char **args, t_varenv *varenv)
{
	char		*pwd;
	t_varenv	*start;

	start = varenv;
	pwd = malloc(sizeof(char) * 256);
	if (args[2])
	{
		ft_putstr("cd: string not in pwd: ");
		ft_putendl(args[2]);
		return ;
	}
	while (varenv)
	{
		if (!ft_strcmp("PWD", ft_strsplit(varenv->var, '=')[0]))
			pwd = ft_strcpy(pwd, ft_strsplit(varenv->var, '=')[1]);
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
