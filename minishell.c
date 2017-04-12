/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 16:16:02 by rluder            #+#    #+#             */
/*   Updated: 2017/04/12 22:01:17 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include "libft/libft.h"
#include "get_next_line.h"
#include "minishell.h"

t_varenv	*create_varenv(char *env)
{
	t_varenv	*varenv;

	varenv = malloc(sizeof(t_varenv));
	if (!varenv)
		return (NULL);
	varenv->var = env;
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

void	do_env(t_varenv	*varenv)
{
	while (varenv)
	{
		if (varenv->var && ft_strcmp(varenv->var, "\0") != 0)
			ft_putendl(varenv->var);
		varenv = varenv->next;
	}
}

/*t_varenv	*del_varenv(t_varenv *varenv, char *name)
{
	t_varenv	*prev;
	t_varenv	*next;
	t_varenv	*start;

	start = varenv;
	prev = varenv;
	while (varenv)
	{
		if (prev == start)
		{
			if (!ft_strcmp(name, ft_strsplit(varenv->var, '=')[0]))
				start = varenv->next;
		}
		else
		{
			if (!ft_strcmp(name, ft_strsplit(varenv->var, '=')[0]))
			{
				varenv = prev;
				prev->next = varenv->next;
			}
		}
		varenv = varenv->next;
		prev = varenv;
	}
	return (start);
}*/

void	remove_node(t_varenv *start, t_varenv *varenv)
{
	t_varenv	*temp;
	t_varenv	*current;
	t_varenv	*previous;

	if (ft_strcmp(varenv->var, start->var) == 0)
	{
		temp = start;
		start = start->next;
		free (temp);
		return;
	}
	current = start->next;
	previous = start;
	while (current != NULL && previous != NULL)
	{
		if (ft_strcmp(varenv->var, current->var) == 0)
		{
			temp = current;
			previous->next = current->next;
			free (temp);
			return;
		}
		previous = current;
		current = current->next;
	}
	return;
}

void	do_unsetenv(char **args, t_varenv *varenv)
{
	int			i;
	t_varenv	*start;
	t_varenv	*temp;

	i = 1;
	start = varenv;
	while (args[i])
	{
		varenv = start;
		while (varenv)
		{
			if (!ft_strcmp(args[i], ft_strsplit(varenv->var, '=')[0]))
			{
				remove_node(start, varenv);
			}
			varenv = varenv->next;
		}
		i++;
	}
	varenv = start;
}

void	do_setenv(char **args, t_varenv *varenv)
{
	int	i;
	int j;
	t_varenv	*start;
	t_varenv	*tmp;

	i = 1;
	start = varenv;
	while (args[i])
	{
		varenv = start;
		while (varenv)
		{
			if (!ft_strcmp(ft_strsplit(args[i], '=')[0], ft_strsplit(varenv->var, '=')[0]))
			{
				varenv->var = args[i];
				return;
			}
			varenv = varenv->next;
		}
		varenv = start;
		while (varenv->next)
			varenv = varenv->next;
		varenv->next = create_varenv(args[i]);
		i++;
	}
	varenv = start;
}

void	go_pwd(t_varenv *varenv)
{
	t_varenv	*var1;
	t_varenv	*var2;
	char		*home;

	var1 = varenv;
	while (varenv)
	{
		if (!ft_strcmp("HOME", ft_strsplit(varenv->var, '=')[0]))
			home = ft_strcpy(home, ft_strsplit(varenv->var, '=')[1]);
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
			varenv->var = ft_strcpy(varenv->var, ft_strjoin("PWD=", pwd));
		if (!ft_strcmp("OLDPWD", ft_strsplit(varenv->var, '=')[0]))
			varenv->var = ft_strcpy(varenv->var, ft_strjoin("OLDPWD=", pwd));
		varenv = varenv->next;
	}
	varenv = start;
}

void	change_dir(char **args, t_varenv *varenv)
{
	ft_putendl("nope, not done");
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
	int	addc;
	int	start;
	int	i;
	char **args2;

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

void	dobuiltin(char **args, t_varenv *varenv)
{
	if (!ft_strcmp(args[0], "env"))
	{
		do_env(varenv);
		ft_putendl("inenv");
	}
	else if (!ft_strcmp(args[0], "unsetenv") && args[1])
	{
		do_unsetenv(args, varenv);
		ft_putendl("inunsetenv");
	}
	else if (!ft_strcmp(args[0], "unsetenv") && !args[1])
	{
		ft_putendl("unsetenv: not enough arguments");
		ft_putendl("inunsetenv");
	}
	else if (!ft_strcmp(args[0], "setenv") && ft_strchr(args[1], '='))
	{
		do_setenv(args, varenv);
		ft_putendl("insetenv");
	}
	else if (!ft_strcmp(args[0], "cd"))
	{
		do_cd(args, varenv);
		ft_putendl("incd");
	}
	else if (!ft_strcmp(args[0], "echo"))
	{
		do_echo(args, varenv);
		ft_putendl("inecho");
	}
}

char	**unpack_path(t_varenv *varenv)
{
	char	*unpack;
	char	**path;

	while (varenv)
	{
		if (ft_strcmp("PATH", ft_strsplit(varenv->var, '=')[0]))
			unpack = ft_strcpy(unpack, ft_strsplit(varenv->var, '=')[1]);
		varenv = varenv->next;
	}
	path = ft_strsplit(unpack, ':');
	return (path);
}


char	*unpack_pwd(t_varenv *varenv)
{
	char	*pwd;

	while (varenv)
	{
		if (ft_strcmp("PWD", ft_strsplit(varenv->var, '=')[0]))
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
	path = unpack_path(varenv);
	while (exists != 1 && path[i])
	{
		if (access(ft_strjoin(ft_strjoin(path[i], "/"), args[0]), F_OK))
			exists = 1;
		else
			i++;
	}
	if (exists == 1)
		exec_process(ft_strjoin(ft_strjoin(path[i], "/"), args[0]), args, varenv);
	else
	{
		pwd = unpack_pwd(varenv);
		if (access(ft_strjoin(ft_strjoin(pwd, "/"), args[0]), F_OK))
		{
			exec_process(ft_strjoin(ft_strjoin(pwd, "/"), args[0]), args, varenv);
		}
		else
		{
			ft_putstr("minishell: command not found\n");
			ft_putendl(args[0]);
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
	int			test;

	input = NULL;
	if (argc != 1 && !argv)
		return (0);
	varenv = stockenv(env);
	while (1)
	{
		test = 0;
		ft_putstr("$>");
		get_next_line(0, &input);
		line = ft_strdup(input);
		ft_memdel((void**)&input);
		args = ft_strsplit(notabs(line), ' ');
		if (!ft_strcmp(args[0], "exit"))
		{
			free(line);
			free(args);
			ft_putendl("free done");
			return (0);
		}
		else if (isbuiltin(args) == 1)
		{
			dobuiltin(args, varenv);
			ft_putendl("dobuiltin done");
		}
		else if (isbuiltin(args) == 0)
		{
			process(args, varenv);
			ft_putendl("process done");
		}
	}
	return (0);
}
