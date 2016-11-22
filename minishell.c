/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 16:16:02 by rluder            #+#    #+#             */
/*   Updated: 2016/11/22 09:16:11 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "libft/libft.h"
#include "get_next_line.h"
#include "minishell.h"

t_varenv	stockenv(char **env)
{
	int			i;
	char		**cutpath;
	t_varenv	varenv;

	i = 0;
	while (env[i++])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			 cutpath = ft_strsplit(ft_strdup(env[i]), '=');
			 varenv.path = ft_strdup(cutpath[1]);
		}
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			 cutpath = ft_strsplit(ft_strdup(env[i]), '=');
			 varenv.pwd = ft_strdup(cutpath[1]);
		}
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			 cutpath = ft_strsplit(ft_strdup(env[i]), '=');
			 varenv.oldpwd = ft_strdup(cutpath[1]);
		}
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
		{
			 cutpath = ft_strsplit(ft_strdup(env[i]), '=');
			 varenv.home = ft_strdup(cutpath[1]);
		}
	}
	return (varenv);
}

int	main(int argc, char **argv, char **env)
{
	int			status;
	char		*input;
	char		*line;
	char		**args;
	t_varenv	varenv;

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
		args = ft_strsplit(line, ' ');
/*		if (!isbuiltin(line) && !shell(args, varenv))
			program(args, varenv);
		else if (!isbuiltin(line))
			process(args, varenv);
		else if (isbuiltin(line) && ft_strcmp(args[0], "exit"))
			dobuiltin(args, &varenv);
		else if (!ft_strcmp(args[0], "exit"))
		{
			free(line);
			free(args);
			return (0);
		}*/
	}
	return (0);
}
