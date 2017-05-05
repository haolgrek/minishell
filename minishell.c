/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 16:16:02 by rluder            #+#    #+#             */
/*   Updated: 2017/05/05 20:21:40 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h>
#include "libft/libft.h"
#include "get_next_line.h"
#include "minishell.h"

t_varenv	*create_varenv(char *env)
{
	t_varenv	*varenv;

	varenv = malloc(sizeof(t_varenv));
	ft_bzero(varenv, sizeof(t_varenv));
	if (env)
	{
		varenv->var = malloc(sizeof(char) * 256);
		varenv->var = ft_strcpy(varenv->var, env);
	}
	varenv->next = NULL;
	return (varenv);
}

t_varenv	*stockenv(char **env)
{
	int			i;
	t_varenv	*varenv[2];

	i = 0;
	varenv[0] = NULL;
	while (env[i])
	{
		if (i == 0)
		{
			varenv[1] = create_varenv(env[i]);
			varenv[0] = varenv[1];
			i++;
		}
		else
		{
			varenv[1]->next = create_varenv(env[i]);
			varenv[1] = varenv[1]->next;
			i++;
		}
	}
	return (varenv[0]);
}

int	isbuiltin(char **args)
{
	if (ft_strcmp(args[0], "cd") == 0 || ft_strcmp(args[0], "env") == 0 ||
			ft_strcmp(args[0], "setenv") == 0 ||
			ft_strcmp(args[0], "unsetenv") == 0 ||
			ft_strcmp(args[0], "echo") == 0)
		return (1);
	return (0);
}

void	print_env(t_varenv *varenv, int izi)
{
	if (izi == 1)
		return ;
	while (varenv)
	{
		if (varenv->var && ft_strcmp(varenv->var, "\0") != 0)
			ft_putendl(varenv->var);
		varenv = varenv->next;
	}
}

void	do_env2(t_varenv *varenv, char **args, int i, int izi)
{
	if (!args[i])
	{
		print_env(varenv, izi);
		return ;
	}
	else if (ft_strchr(args[i], '='))
	{
		print_env(varenv, izi);
		do_new_setenv(args, i);
	}
	else
	{
		ft_putstr("env: ");
		ft_putstr(args[i]);
		ft_putendl(": No such file or directory");
	}
}

void	do_env(t_varenv *varenv, char **args)
{
	int	i;
	int	izi;

	izi = 0;
	if (!args[1])
	{
		print_env(varenv, izi);
		return ;
	}
	i = 1;
	while (args[i] && (ft_strcmp(args[i], "-i") == 0 ||
			ft_strcmp(args[i], "env") == 0))
	{
		if (ft_strcmp(args[i], "-i") == 0)
		{
			izi = 1;
			i++;
		}
		if (args[i] && ft_strcmp(args[i], "env") == 0)
			i++;
	}
	do_env2(varenv, args, i, izi);
}

t_varenv	*remove_start(t_varenv *start)
{
	t_varenv	*temp;

	temp = start;
	start = start->next;
	free(temp);
	return (start);
}

t_varenv	*remove_current(t_varenv *start, t_varenv *cur, t_varenv *prev)
{
	t_varenv	*temp;

	temp = cur;
	prev->next = cur->next;
	free(temp);
	return (start);
}

t_varenv	*remove_node(t_varenv *start, t_varenv *varenv)
{
	t_varenv	*current;
	t_varenv	*previous;

	if (start->var)
	{
		if (ft_strcmp(varenv->var, start->var) == 0)
			return (remove_start(start));
	}
	current = start->next;
	previous = start;
	while (current != NULL && previous != NULL)
	{
		if (varenv->var)
		{
			if (ft_strcmp(varenv->var, current->var) == 0)
				return (remove_current(start, current, previous));
		}
		previous = current;
		current = current->next;
	}
	return (start);
}

t_varenv	*do_unsetenv(char **args, t_varenv *varenv)
{
	int			i;
	int			j;
	t_varenv	*start;
	t_varenv	*temp;

	i = 1;
	j = 0;
	if (!varenv->var && !varenv->next)
		return (varenv);
	start = varenv;
	while (args[i])
	{
		varenv = start;
		while (varenv && args[i])
		{
			if (varenv->var)
			{
				if (!ft_strcmp(args[i], ft_strsplit(varenv->var, '=')[0]))
					start = remove_node(start, varenv);
			}
			varenv = varenv->next;
		}
		i++;
	}
	varenv = start;
	return (start);
}

t_varenv	*do_setenv(char **args, t_varenv *varenv)
{
	int			i;
	int			j;
	t_varenv	*start;
	t_varenv	*tmp;

	i = 1;
	if (!varenv)
		varenv = create_varenv(NULL);
	start = varenv;
	while (args[i])
	{
		j = 0;
		varenv = start;
		while (varenv && varenv->var && args[i])
		{
			if (varenv->var)
			{
				if (!ft_strcmp(ft_strsplit(args[i], '=')[0],
					ft_strsplit(varenv->var, '=')[0]))
				{
					varenv->var = args[i];
					j = 1;
				}
			}
			varenv = varenv->next;
		}
		varenv = start;
		while (varenv->next)
			varenv = varenv->next;
		if (j != 1)
			varenv->next = create_varenv(args[i]);
		i++;
	}
	varenv = start;
	return (varenv);
}

void	go_pwd(t_varenv *varenv)
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
	while (varenv)
	{
		if (!ft_strcmp("PWD", ft_strsplit(varenv->var, '=')[0]))
			varenv->var = ft_strjoin("PWD=", home);
		varenv = varenv->next;
	}
	varenv = var1;
}

void	revert_pwd(t_varenv *varenv)
{
	char		*pwd;
	char		*oldpwd;
	t_varenv	*start;

	start = varenv;
	pwd = malloc(sizeof(char) * 256);
	oldpwd = malloc(sizeof(char) * 256);
	while (varenv)
	{
		if (!ft_strcmp("PWD", ft_strsplit(varenv->var, '=')[0]))
			pwd = ft_strcpy(pwd, ft_strsplit(varenv->var, '=')[1]);
		varenv = varenv->next;
	}
	varenv = start;
	while (varenv)
	{
		if (!ft_strcmp("OLDPWD", ft_strsplit(varenv->var, '=')[0]))
			oldpwd = ft_strcpy(oldpwd, ft_strsplit(varenv->var, '=')[1]);
		varenv = varenv->next;
	}
	varenv = start;
	while (varenv)
	{
		if (!ft_strcmp("PWD", ft_strsplit(varenv->var, '=')[0]))
			varenv->var = ft_strcpy(varenv->var, ft_strjoin("PWD=", oldpwd));
		if (!ft_strcmp("OLDPWD", ft_strsplit(varenv->var, '=')[0]))
			varenv->var = ft_strcpy(varenv->var, ft_strjoin("OLDPWD=", pwd));
		varenv = varenv->next;
	}
	varenv = start;
	free(pwd);
	free(oldpwd);
}

void	new_pwd(char *arg, t_varenv *varenv)
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

void	change_dir(char **args, t_varenv *varenv)
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
	else
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
	free(pwd);
}

void	do_cd(char **args, t_varenv *varenv)
{
	if (!args[1])
		go_pwd(varenv);
	else if (!ft_strcmp(args[1], "-"))
		revert_pwd(varenv);
	else
		change_dir(args, varenv);
}

void	do_echo(char **args, t_varenv *varenv)
{
	int		addc;
	int		start;
	int		i;
	char	**args2;

	i = 1;
	addc = 0;
	if (args[1])
	{
		if (!ft_strcmp(args[1], "-n"))
		{
			addc = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr(args[i]);
			if (args[i + 1])
				ft_putchar(' ');
			i++;
		}
	}
	if (addc == 0)
		ft_putchar('\n');
}

void	dobuiltin(char **args, t_varenv **varenv)
{
	if (!ft_strcmp(args[0], "unsetenv") && args[1])
	{
		if (varenv)
			*varenv = do_unsetenv(args, *varenv);
		else
			return ;
	}
	else if (!ft_strcmp(args[0], "env"))
		do_env(*varenv, args);
	else if (!ft_strcmp(args[0], "unsetenv") && !args[1])
		ft_putendl("unsetenv: not enough arguments");
	else if (!ft_strcmp(args[0], "setenv") && !args[1])
		ft_putendl("setenv: not enough arguments");
	else if (!ft_strcmp(args[0], "setenv") && ft_strchr(args[1], '='))
		*varenv = do_setenv(args, *varenv);
	else if (!ft_strcmp(args[0], "cd"))
		do_cd(args, *varenv);
	else if (!ft_strcmp(args[0], "echo"))
		do_echo(args, *varenv);
}

char	**unpack_path(t_varenv *varenv)
{
	char	*unpack;
	char	**path;

	unpack = malloc(sizeof(char) * 255);
	while (varenv)
	{
		if (!ft_strcmp("PATH", ft_strsplit(varenv->var, '=')[0]))
			unpack = ft_strcpy(unpack, ft_strsplit(varenv->var, '=')[1]);
		varenv = varenv->next;
	}
	path = ft_strsplit(unpack, ':');
	free(unpack);
	return (path);
}

char	*unpack_pwd(t_varenv *varenv)
{
	char	*pwd;

	pwd = malloc(sizeof(char) * 255);
	while (varenv)
	{
		if (!ft_strcmp("PWD", ft_strsplit(varenv->var, '=')[0]))
			pwd = ft_strcpy(pwd, ft_strsplit(varenv->var, '=')[1]);
		varenv = varenv->next;
	}
	return (pwd);
}

char	**redo_env(t_varenv *varenv)
{
	t_varenv	*start;
	int			i;
	char		**env;

	i = 0;
	start = varenv;
	while (varenv)
	{
		i++;
		varenv = varenv->next;
	}
	varenv = start;
	env = malloc(sizeof(char *) * i);
	i = 0;
	while (env[i])
	{
		env[i] = ft_strcpy(env[i], varenv->var);
		i++;
	}
	return (env);
}

void	exec_process(char *path, char **args, t_varenv *varenv)
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
		exec_process(ft_strjoin(ft_strjoin(path[i], "/"),
			args[0]), args, varenv);
	else
	{
		pwd = unpack_pwd(varenv);
		if (!access(ft_strjoin(ft_strjoin(pwd, "/"), args[0]), X_OK))
			exec_process(ft_strjoin(ft_strjoin(pwd, "/"),
				args[0]), args, varenv);
		else
		{
			if (args[0][0] == '/')
			{
				if (!access(args[0], X_OK))
					exec_process(args[0], args, varenv);
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
	}
}

char	*notabs(char *line)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(line) + 1));
	while (line[i])
	{
		str[i] = line[i];
		if (line[i] == '\t')
			str[i] = ' ';
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	char		*line;
	char		**args;
	t_varenv	*varenv;

	input = NULL;
	if (argc != 1 && !argv)
		return (0);
	varenv = stockenv(env);
	while (1)
	{
		ft_putstr("$>");
		if (get_next_line(0, &input) < 0)
			return (0);
		line = ft_strdup(input);
		ft_memdel((void**)&input);
		args = ft_strsplit(notabs(line), ' ');
		if (args[0])
		{
			if (!ft_strcmp(args[0], "exit"))
			{
				free(line);
				free(args);
				return (0);
			}
			else if (isbuiltin(args) == 1)
				dobuiltin(args, &varenv);
			else if (isbuiltin(args) == 0)
				process(args, varenv);
		}
	}
	return (0);
}
