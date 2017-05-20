/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strsplit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/13 08:31:16 by rluder            #+#    #+#             */
/*   Updated: 2016/01/05 18:15:38 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_free_strsplit(char **tab)
{
	unsigned int	y;

	y = 0;
	while (tab[y] != NULL)
	{
		free(tab[y]);
		tab[y++] = NULL;
	}
	free(tab);
	tab = NULL;
	return (NULL);
}
