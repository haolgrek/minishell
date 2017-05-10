/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 02:25:11 by rluder            #+#    #+#             */
/*   Updated: 2017/05/10 18:19:45 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_varenv		*create_varenv(char *env)
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

t_varenv		*stockenv(char **env)
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

char			*notabs(char *line)
{
	int			i;
	char		*str;

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

void			chooseoptions(char **args, char *line, t_varenv *varenv)
{
	if (!ft_strcmp(args[0], "exit"))
	{
		free(line);
		free(args);
		exit(0);
	}
	else if (isbuiltin(args) == 1)
		dobuiltin(args, varenv);
	else if (isbuiltin(args) == 0)
		process(args, varenv);
}

int				main(int argc, char **argv, char **env)
{
	char		*input;
	char		*line;
	char		**args;
	t_varenv	*varenv;

	input = NULL;
	if (argc != 1 && !argv)
		return (0);
	varenv = stockenv(env);
	if (!varenv)
		varenv = create_varenv("\r");
	while (1)
	{
		ft_putstr("$>");
		if (get_next_line(0, &input) < 0)
			return (0);
		line = ft_strdup(input);
		ft_memdel((void**)&input);
		args = ft_strsplit(notabs(line), ' ');
		if (args[0])
			chooseoptions(args, line, varenv);
	}
	return (0);
}
