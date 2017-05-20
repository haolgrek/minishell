/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/12 07:59:56 by rluder            #+#    #+#             */
/*   Updated: 2015/11/24 22:19:46 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memalloc(size_t n)
{
	void		*variable;

	if ((variable = malloc(n)) == NULL)
		return (NULL);
	ft_bzero(variable, n);
	return (variable);
}
