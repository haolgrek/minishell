/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 11:39:59 by rluder            #+#    #+#             */
/*   Updated: 2015/12/09 17:55:51 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <time.h>

int				ft_rand(int min, int max)
{
	static int	loop;

	if (loop == 0)
		srand(time(NULL));
	loop = 1;
	return ((rand() % (max - min + 1)) + min);
}
