/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/02 16:23:23 by rluder            #+#    #+#             */
/*   Updated: 2015/12/01 09:07:16 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*mem;
	unsigned int	i;

	i = 0;
	mem = (unsigned char *)s;
	while (n)
	{
		mem[i++] = (unsigned char)c;
		n--;
	}
	return (s);
}
