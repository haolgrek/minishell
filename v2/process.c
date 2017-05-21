/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 02:51:10 by rluder            #+#    #+#             */
/*   Updated: 2017/05/21 21:07:33 by rluder           ###   ########.fr       */
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

	env = NULL;
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
}

void			slashornot(char **args, t_varenv *varenv)
{
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
}

void			isslash(t_varenv *varenv, char **args)
{
	char		*pwd;
	char		*tmp;
	char		*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	pwd = NULL;
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
	if (pwd)
		free(pwd);
}

void			endprocess(int i, char *tmp2, char **args, t_varenv *varenv)
{
	if (i == 1)
	{
		ex_pro(tmp2, args, varenv);
		freechars(tmp2);
	}
	else
		isslash(varenv, args);
}

void			process(char **args, t_varenv *varenv, char *tmp, char *tmp2)
{
	char		**path;
	int			i[2];

	i[0] = 0;
	i[1] = 0;
	path = NULL;
	path = unpack_path(varenv);
	while (i[1] != 1 && path && path[i[0]])
	{
		tmp = ft_strjoin(path[i[0]], "/");
		tmp2 = ft_strjoin(tmp, args[0]);
		freechars(tmp);
		if (!access(tmp2, F_OK))
			i[1] = 1;
		else
		{
			free(tmp2);
			i[0]++;
		}
	}
	if (path)
		ft_free_strsplit(path);
	endprocess(i[1], tmp2, args, varenv);
}
