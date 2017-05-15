/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 02:51:10 by rluder            #+#    #+#             */
/*   Updated: 2017/05/15 21:23:54 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void			ex_pro(char *path, char **args, t_varenv *varenv)
{
	id_t		pid;
	int			status;
	char		**env;
	struct stat	st;

//	ft_putendl("expro");
	if (lstat(path, &st) == 0 && st.st_mode & S_IFDIR)
	{
		ft_putendl("minishell: command not found");
		return ;
	}
	env = redo_env(varenv);
	pid = fork();
	if (pid > 0)
		wait(&status);
	if (pid == 0)
	{
		if (execve(path, args, env) == -1)
		{
			ft_putendl("minishell: not an executable file");
			exit(EXIT_FAILURE);
		}
		kill(pid, 9);
	}
	letsfree(env);
//	ft_putendl("outexpro");
}

void			slashornot(char **args, t_varenv *varenv)
{
//	ft_putendl("slashornot");
	if (args[0][0] == '/')
	{
		if (!access(args[0], X_OK))
			ex_pro(args[0], args, varenv);
		else
		{
			ft_putstr("minishell: command not found: ");
			ft_putendl(args[0]);
		}
	}
	else
	{
		ft_putstr("minishell: command not found: ");
		ft_putendl(args[0]);
	}
//	ft_putendl("outslashornot");
}

void			isslash(char *pwd, t_varenv *varenv, char **args)
{
	char		*tmp;
	char		*tmp2;

//	ft_putendl("isslash");
	pwd = unpack_pwd(varenv);
	tmp = ft_strjoin(pwd, "/");
	tmp2 = ft_strjoin(tmp, args[0]);
	if (pwd && !access(tmp2, X_OK))
		ex_pro(tmp2, args, varenv);
	else
		slashornot(args, varenv);
	if (tmp2)
		free(tmp2);
	if (tmp)
		free(tmp);
//	ft_putendl("outisslash");
}

int				isdir(char *args)
{
	int			i;

//	ft_putendl("isdir");
	i = 0;
	while (args[i])
		i++;
	if (args[i - 1] == '/')
		return (0);
//	ft_putendl("outisdir");
	return (1);
}

void			process(char **args, t_varenv *varenv)
{
	char		**path;
	char		*pwd;
	int			i;
	int			exists;
	char		*tmp;
	char		*tmp2;

//	ft_putendl("process");
	i = 0;
	exists = 0;
	if (!varenv || !varenv->var || isdir(args[0]) == 0)
	{
		ft_putstr("minishell: command not found: ");
		ft_putendl(args[0]);
		return ;
	}
	path = unpack_path(varenv);
	while (exists != 1 && path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp, args[0]);
		if (!access(tmp2, F_OK))
			exists = 1;
		else
		{
			if (tmp2)
				ft_memdel((void**)&tmp2);
			i++;
		}
		if (tmp)
			free(tmp);
	}
	letsfree(path);
	if (exists == 1)
	{
//		ft_putendl("in");
		ex_pro(tmp2, args, varenv);
//		ft_putendl("out");
	}
	else
		isslash(pwd, varenv, args);
	if (tmp2)
		ft_memdel((void**)&tmp2);
//	ft_putendl("outprocess");
}
