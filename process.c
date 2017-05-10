/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 02:51:10 by rluder            #+#    #+#             */
/*   Updated: 2017/05/10 18:19:02 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_pro(char *path, char **args, t_varenv *varenv)
{
	id_t	pid;
	int		status;
	char	**env;

	env = redo_env(varenv);
	pid = fork();
	if (pid > 0)
		wait(&status);
	if (pid == 0)
	{
		execve(path, args, env);
		kill(pid, 9);
	}
}

void	slashornot(char **args, t_varenv *varenv)
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

void	isslash(char *pwd, t_varenv *varenv, char **args)
{
	pwd = unpack_pwd(varenv);
	if (!access(ft_strjoin(ft_strjoin(pwd, "/"), args[0]), X_OK))
	{
		ex_pro(ft_strjoin(ft_strjoin(pwd, "/"),
			args[0]), args, varenv);
	}
	else
		slashornot(args, varenv);
}

void	process(char **args, t_varenv *varenv)
{
	char	**path;
	char	*pwd;
	int		i;
	int		exists;

	i = 0;
	exists = 0;
	if (!varenv || !varenv->var)
	{
		ft_putstr("minishell: command not found: ");
		ft_putendl(args[0]);
		return ;
	}
	path = unpack_path(varenv);
	while (exists != 1 && path[i])
	{
		if (!access(ft_strjoin(ft_strjoin(path[i], "/"), args[0]), F_OK))
			exists = 1;
		else
			i++;
	}
	if (exists == 1)
		ex_pro(ft_strjoin(ft_strjoin(path[i], "/"), args[0]), args, varenv);
	else
		isslash(pwd, varenv, args);
}
