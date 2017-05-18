/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 15:56:33 by rluder            #+#    #+#             */
/*   Updated: 2017/05/18 17:01:14 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freechars(char *str)
{
	if (str)
		free(str);
}

void	errorhome(char *home)
{
	ft_putstr("cd: no such file or directory: ");
	ft_putendl(home);
}

void	errorcd(char *arg)
{
	ft_putstr("cd: string not in pwd: ");
	ft_putendl(arg);
}

void	letsfree(char **env)
{
	int	i;

	i = 0;
	if (env)
	{
		while (env[i])
		{
			free(env[i]);
			i++;
		}
		free(env);
	}
}
