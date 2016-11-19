/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 16:16:02 by rluder            #+#    #+#             */
/*   Updated: 2016/11/19 18:53:38 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "libft/libft.h"
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		status;
	char	*input;
	char	*line;
	char	**args;



	status = 0;
	input = NULL;

	while (1)
	{
		ft_putstr("$>");
		get_next_line(0, &input);
		line = ft_strdup(input);
		ft_memdel((void**)&input);
		args = ft_strsplit(input, ' ');
//		args = split_by_space(input);
//		status = execute(args);
//		free(input);
//		free(args);
	}
}
