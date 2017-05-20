/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 09:34:48 by rluder            #+#    #+#             */
/*   Updated: 2015/11/24 22:20:07 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*mem_s1;
	unsigned char	*mem_s2;

	mem_s1 = (unsigned char *)s1;
	mem_s2 = (unsigned char *)s2;
	while (n)
	{
		if (*mem_s1 != *mem_s2)
			return (*mem_s1 - *mem_s2);
		n--;
		mem_s1++;
		mem_s2++;
	}
	return (0);
}
