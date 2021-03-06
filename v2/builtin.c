/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 05:47:39 by rluder            #+#    #+#             */
/*   Updated: 2017/05/21 20:59:34 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			go_pwd(t_varenv *varenv)
{
	t_varenv	*var1;
	char		*home;
	char		**tmp;

	var1 = varenv;
	home = NULL;
	tmp = NULL;
	while (varenv)
	{
		tmp = ft_strsplit(varenv->var, '=');
		if (!ft_strcmp("HOME", tmp[0]))
		{
			if (ft_strlen(tmp[1]) < 256)
			{
				home = ft_memalloc(ft_strlen(tmp[1]) + 1);
				home = ft_strcpy(home, tmp[1]);
			}
		}
		letsfree(tmp);
		varenv = varenv->next;
	}
	varenv = var1;
	do_home(home, varenv);
	varenv = var1;
	freechars(home);
}

int				change_arg(t_varenv *varenv, char **args, int i)
{
	int			j;
	char		**tmp;
	char		**tmp2;

	j = 0;
	tmp = NULL;
	tmp2 = NULL;
	while (varenv && varenv->var && args[i])
	{
		if (varenv->var)
		{
			tmp = ft_strsplit(args[i], '=');
			tmp2 = ft_strsplit(varenv->var, '=');
			if (!ft_strcmp(tmp[0], tmp2[0]) && ft_strchr(args[i], '='))
			{
				varenv->var = ft_memalloc(ft_strlen(args[i]) + 1);
				varenv->var = ft_strcpy(varenv->var, args[i]);
				j = 1;
			}
		}
		letsfree(tmp);
		letsfree(tmp2);
		varenv = varenv->next;
	}
	return (j);
}

t_varenv		*do_setenv(char **args, t_varenv *varenv)
{
	int			i;
	int			j;
	char		**newenv;
	t_varenv	*start;

	i = 1;
	newenv = NULL;
	start = varenv;
	while (args[i])
	{
		j = 0;
		varenv = start;
		j = change_arg(varenv, args, i);
		varenv = start;
		while (varenv->next)
			varenv = varenv->next;
		if (j != 1 && ft_strchr(args[i], '='))
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

void			dobuiltin(char **args, t_varenv *varenv)
{
	if (!ft_strcmp(args[0], "unsetenv") && args[1])
	{
		if (varenv)
			do_unsetenv(args, varenv);
		else
			return ;
	}
	else if (!ft_strcmp(args[0], "env"))
		do_env(varenv, args);
	else if (!ft_strcmp(args[0], "unsetenv") && !args[1])
		ft_putendl("unsetenv: not enough arguments");
	else if (!ft_strcmp(args[0], "setenv") && !args[1])
		ft_putendl("setenv: not enough arguments");
	else if (!ft_strcmp(args[0], "setenv") && ft_strchr(args[1], '='))
		do_setenv(args, varenv);
	else if (!ft_strcmp(args[0], "cd"))
		do_cd(args, varenv);
	else if (!ft_strcmp(args[0], "echo"))
		do_echo(args, varenv);
}
