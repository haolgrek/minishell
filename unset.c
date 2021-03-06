/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 05:39:44 by rluder            #+#    #+#             */
/*   Updated: 2017/05/09 00:04:05 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_varenv		*remove_start(t_varenv *start)
{
	t_varenv	*temp;

	temp = start;
	start = start->next;
	free(temp);
	return (start);
}

t_varenv		*remove_current(t_varenv *start, t_varenv *cur, t_varenv *prev)
{
	t_varenv	*temp;

	temp = cur;
	prev->next = cur->next;
	free(temp);
	return (start);
}

t_varenv		*remove_node(t_varenv *start, t_varenv *varenv)
{
	t_varenv	*current;
	t_varenv	*previous;

	if (start->var)
	{
		if (ft_strcmp(varenv->var, start->var) == 0)
			return (remove_start(start));
	}
	current = start->next;
	previous = start;
	while (current != NULL && previous != NULL)
	{
		if (varenv->var)
		{
			if (ft_strcmp(varenv->var, current->var) == 0)
				return (remove_current(start, current, previous));
		}
		previous = current;
		current = current->next;
	}
	return (start);
}

t_varenv		*do_unsetenv(char **args, t_varenv *varenv)
{
	int			i;
	t_varenv	*start;
	t_varenv	*temp;

	i = 1;
	if (!varenv || (!varenv->var && !varenv->next))
		return (varenv);
	start = varenv;
	while (args[i])
	{
		varenv = start;
		while (varenv && args[i])
		{
			if (varenv->var)
			{
				if (!ft_strcmp(args[i], ft_strsplit(varenv->var, '=')[0]))
					start = remove_node(start, varenv);
			}
			varenv = varenv->next;
		}
		i++;
	}
	varenv = start;
	return (start);
}
