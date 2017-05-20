/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   revert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 17:32:43 by rluder            #+#    #+#             */
/*   Updated: 2017/05/21 00:02:29 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			revertwhile1(t_varenv *varenv, char *pwd)
{
	char	**tmp;

	tmp = NULL;
	while (varenv)
	{
		tmp = ft_strsplit(varenv->var, '=');
		if (!ft_strcmp("PWD", tmp[0]))
			pwd = ft_strcpy(pwd, tmp[1]);
		letsfree(tmp);
		varenv = varenv->next;
	}
}

void			revertwhile2(t_varenv *varenv, char *oldpwd)
{
	char	**tmp;

	tmp = NULL;
	while (varenv)
	{
		tmp = ft_strsplit(varenv->var, '=');
		if (!ft_strcmp("OLDPWD", tmp[0]))
			oldpwd = ft_strcpy(oldpwd, tmp[1]);
		letsfree(tmp);
		varenv = varenv->next;
	}
}

char			*notabs(char *line)
{
	int			i;
	char		*str;

	str = NULL;
	i = 0;
	str = ft_memalloc(ft_strlen(line) + 1);
	while (line[i])
	{
		str[i] = line[i];
		if (line[i] == '\t')
			str[i] = ' ';
		i++;
	}
	return (str);
}
