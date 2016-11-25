/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 16:16:02 by rluder            #+#    #+#             */
/*   Updated: 2016/11/25 17:50:15 by rluder           ###   ########.fr       */
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
	return (NULL);
}

int	dobuiltin(char **args, t_varenv *varenv)
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

/*print varenv
	while (varenv)
	{
		ft_putendl(varenv->var);
		varenv = varenv->next;
	}*/

	while (1)
	{
		ft_putstr("$>");
		get_next_line(0, &input);
		line = ft_strdup(input);
		ft_memdel((void**)&input);
		args = ft_strsplit(line, ' ');
		if (!isbuiltin(args) && !shell(args, varenv))
			program(args, varenv);
		else if (!isbuiltin(args))
			process(args, varenv);
		else if (isbuiltin(args) && ft_strcmp(args[0], "exit"))
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
