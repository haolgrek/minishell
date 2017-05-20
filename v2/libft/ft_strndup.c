/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 19:36:37 by rluder            #+#    #+#             */
/*   Updated: 2015/12/13 14:35:38 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(const char *s, size_t len)
{
	char			*dup;
	size_t			len_s;

	if ((len_s = ft_strlen(s)) < len)
		len = len_s;
	if ((dup = malloc((len + 1) * sizeof(char))) == NULL)
		return (NULL);
	dup[len] = '\0';
	return (ft_strncpy(dup, s, len));
}
