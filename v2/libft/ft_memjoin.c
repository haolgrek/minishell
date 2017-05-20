/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 10:52:07 by rluder            #+#    #+#             */
/*   Updated: 2016/01/19 22:18:16 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memjoin(const void *src1, size_t n_src1, const
		void *src2, size_t n_src2)
{
	char			*cpy_src1;
	char			*cpy_src2;
	char			*ret;
	char			*adr;

	cpy_src1 = (char *)src1;
	cpy_src2 = (char *)src2;
	if ((ret = ft_memalloc(n_src1 + n_src2)) != NULL)
	{
		adr = ret;
		while (n_src1-- > 0)
			*adr++ = *cpy_src1++;
		while (n_src2-- > 0)
			*adr++ = *cpy_src2++;
	}
	return (ret);
}
