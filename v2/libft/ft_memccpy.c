/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memccpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 20:58:20 by rluder            #+#    #+#             */
/*   Updated: 2015/12/01 09:12:07 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*mem_dest;
	unsigned char	*mem_src;

	i = 0;
	mem_dest = (unsigned char*)dest;
	mem_src = (unsigned char*)src;
	while (i < n)
	{
		mem_dest[i] = mem_src[i];
		if (mem_src[i++] == (unsigned char)c)
			return (&mem_dest[i]);
	}
	return (NULL);
}
