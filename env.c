/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 15:44:16 by rluder            #+#    #+#             */
/*   Updated: 2017/04/18 16:53:24 by rluder           ###   ########.fr       */
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
