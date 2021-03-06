/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_wout_spc_be.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/12 09:45:32 by rluder            #+#    #+#             */
/*   Updated: 2015/11/24 22:25:00 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlen_wout_spc_be(const char *s)
{
	unsigned int	len;
	unsigned int	mem;

	if (s == NULL)
		return (0);
	len = 0;
	mem = 0;
	while (*s == ' ' || *s == '\t' || *s == '\n')
		s++;
	while (*s != '\0')
	{
		if (*s != ' ' && *s != '\t' && *s != '\n')
		{
			len += mem;
			mem = 0;
			len++;
		}
		else
			mem++;
		s++;
	}
	return (len);
}
