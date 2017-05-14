/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 02:51:10 by rluder            #+#    #+#             */
/*   Updated: 2017/05/14 22:38:25 by rluder           ###   ########.fr       */
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

void			isslash(char *pwd, t_varenv *varenv, char **args)
{
	char		*tmp;
	char		*tmp2;

	pwd = unpack_pwd(varenv);
	tmp = ft_strjoin(pwd, "/");
	tmp2 = ft_strjoin(tmp, args[0]);
	if (pwd && !access(tmp2, X_OK))
		ex_pro(tmp2, args, varenv);
	else
		slashornot(args, varenv);
	free(tmp2);
	free(tmp);
}

int				isdir(char *args)
{
	int			i;

	i = 0;
	while (args[i])
		i++;
	if (args[i - 1] == '/')
		return (0);
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
			i++;
		free(tmp);
		free(tmp2);
	}
	i = 0;
	if (path)
	{
		while(path[i])
		{
			free(path[i]);
			i++;
		}
	}
	free(path);
	if (exists == 1)
		ex_pro(tmp2, args, varenv);
	else
		isslash(pwd, varenv, args);
}
