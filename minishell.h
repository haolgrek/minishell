/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 02:42:06 by rluder            #+#    #+#             */
/*   Updated: 2016/11/22 06:23:50 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct	s_varenv
{
	char	*path;
	char	*pwd;
	char	*oldpwd;
	char	*home;
}	t_varenv;
