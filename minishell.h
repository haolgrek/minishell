/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 02:42:06 by rluder            #+#    #+#             */
/*   Updated: 2016/11/23 23:27:56 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct	s_varenv
{
	char	*var;
	struct s_varenv	*next;
}	t_varenv;
