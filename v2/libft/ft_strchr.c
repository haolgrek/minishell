/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 19:08:39 by rluder            #+#    #+#             */
/*   Updated: 2015/12/01 09:40:01 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	char			*adr;
	unsigned int	i;

	adr = (char*)s;
	i = 0;
	while (adr[i] != '\0' && adr[i] != c)
		i++;
	return (adr[i] == c ? (char*)s + i : NULL);
}
