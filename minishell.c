/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 16:16:02 by rluder            #+#    #+#             */
/*   Updated: 2016/12/29 19:39:13 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
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
		if (varenv->var)
			ft_putendl(varenv->var);
		varenv = varenv->next;
	}
}

void	do_unsetenv(char **args, t_varenv *varenv)
{
	int			i;
	t_varenv	*start;

	i = 1;
	start = varenv;
	while (args[i])
	{
		varenv = start;
		while (varenv)
		{
			if (!ft_strncmp(args[i], varenv->var, '='))
				ft_strclr(varenv->var);
			varenv = varenv->next;
		}
		i++;
	}
	varenv = start;
}

/*void	ins_bef_last(char *argi, t_varenv *varenv)
{
	t_varenv	*tmp[2];

	if (varenv->next->next)
	{
		while (varenv->next->next)
		{
			varenv = varenv->next;
		}
		tmp[0] = create_varenv(char *argi);
		tmp[1] = varenv->next->next;
		varenv->next = tmp[0];
		tmp[0]->next = tmp[1];
	}
	else
	{

	}
}*/

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
		j = 0;
		varenv = start;
		while (varenv)
		{
			if (!ft_strcmp(ft_strsplit(args[i], '=')[0], ft_strsplit(varenv->var, '=')[0])) //a refaire, compare jusqua un nombre pas un caractere!
			{
				varenv->var = ft_strcpy(varenv->var, args[i]);
				j = 1;
			}
			varenv = varenv->next;
		}
		if (j == 0)
			varenv->next = create_varenv(args[i]);
	}
	varenv = start;
}

void	go_pwd(t_varenv *varenv)
{
	t_varenv	*var1;
	t_varenv	*var2;

	varenv = start;
	while (varenv)
	{
		if (!ft_strcmp(args[i], varenv->var, '='))
		{
			
		}
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
	start = 0;
	do_args2(args);
	if (!ft_strcmp(args2[1], "-n"))
	{
		addc = 1;
		i++;
	}
	while (args2[i])
	{
		ft_putstr(args2[i]);
		start = 1;
		if (args2[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (addc == 0)
		ft_putchar('\n');
}

void	dobuiltin(char **args, t_varenv *varenv)
{
	if (!ft_strcmp(args[0], "env"))
		do_env(varenv);
	else if (!ft_strcmp(args[0], "unsetenv") && args[1])
		do_unsetenv(args, varenv);
	else if (!ft_strcmp(args[0], "unsetenv") && !args[1])
		ft_putendl("unsetenv: not enough arguments");
	else if (!ft_strcmp(args[0], "setenv"))
		do_setenv(args, varenv);
	else if (!ft_strcmp(args[0], "cd"))
		do_cd(args, varenv);
	else if (!ft_strcmp(args[0], "echo"))
		do_echo(args, varenv);
}

void	*process(char **args, t_varenv *varenv)
{
	do_else avec path;
}
/*
int	(char **args, t_varenv *varenv)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	pid = fork();
	if (pid == 0)
		execve(findpath(varenv), concat_args(args), varenv_totab(varenv));
	else
		wait(&status);
	return (0);
}*/

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
	int			status;
	char		*input;
	char		*line;
	char		**args;
	t_varenv	*varenv;

	status = 0;
	input = NULL;

	if (argc != 1 && !argv)
		return (0);
	varenv = stockenv(env);
	while (1)
	{
		ft_putstr("$>");
		get_next_line(0, &input);
		line = ft_strdup(input);
		ft_memdel((void**)&input);
		args = ft_strsplit(notabs(line), ' ');
		if (isbuiltin(args) == 0)
			process(args, varenv);
		else if (isbuiltin(args) == 1 && ft_strcmp(args[0], "exit"))
			dobuiltin(args, varenv);
		else if (!ft_strcmp(args[0], "exit"))
		{
			free(line);
			free(args);
			return (0);
		}
	}
	return (0);
}
