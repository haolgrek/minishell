/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 05:47:39 by rluder            #+#    #+#             */
/*   Updated: 2017/05/08 20:04:52 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				change_arg(t_varenv *varenv, char **args, int i)
{
	int			j;

	j = 0;
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
	return (j);
}

char			**new_env(char **args)
{
	char	**newenv;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			newenv[j] = malloc(sizeof(char) * (ft_strlen(args[i]) + 1));
			newenv[j] = ft_strcpy(newenv[j], args[i]);
			i++;
			j++;
		}
		else
			i++;
	}
	return (newenv);
}

t_varenv		*do_setenv(char **args, t_varenv *varenv)
{
	int			i;
	int			j;
	char		**newenv;
	t_varenv	*start;

	i = 1;
	if (!varenv)
	{
		ft_putendl("no varenv");
		newenv = new_env(args);
		ft_putendl("newenv done");
		varenv = stockenv(newenv);
		ft_putendl("varenv done");
		return (varenv);
//		varenv = create_varenv(NULL);
	}
	start = varenv;
	while (args[i])
	{
		j = 0;
		varenv = start;
		j = change_arg(varenv, args, i);
		varenv = start;
		while (varenv->next)
			varenv = varenv->next;
		if (j != 1)
			varenv->next = create_varenv(args[i]);
		i++;
	}
	return (start);
}

void			do_echo(char **args, t_varenv *varenv)
{
	int			addc;
	int			start;
	int			i;
	char		**args2;

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

void			dobuiltin(char **args, t_varenv **varenv)
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
	{
		ft_putendl("in");
		*varenv = do_setenv(args, *varenv);
		ft_putendl("out");
	}
	else if (!ft_strcmp(args[0], "cd"))
		do_cd(args, *varenv);
	else if (!ft_strcmp(args[0], "echo"))
		do_echo(args, *varenv);
}
