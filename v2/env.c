/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 15:44:16 by rluder            #+#    #+#             */
/*   Updated: 2017/05/20 23:38:11 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

void	do_new_setenv(char **args, int i)
{
	while (args[i] && ft_strchr(args[i], '='))
	{
		ft_putendl(args[i]);
		i++;
	}
}

int		isbuiltin(char **args)
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
		if (varenv->var && ft_strcmp(varenv->var, "\0") != 0 &&
				varenv->var && ft_strcmp(varenv->var, "\r") != 0)
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
