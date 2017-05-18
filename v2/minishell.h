/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 02:42:06 by rluder            #+#    #+#             */
/*   Updated: 2017/05/18 15:13:42 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <dirent.h>
#include "libft/libft.h"
#include "get_next_line.h"

typedef struct	s_varenv
{
	char	*var;
	struct s_varenv	*next;
}	t_varenv;

void		do_new_setenv(char **args, int i);
t_varenv	*create_varenv(char *env);
int			isbuiltin(char **args);
void		dobuiltin(char **args, t_varenv *varenv);
int			get_next_line(const int fd, char **line);
void		process(char **args, t_varenv *varenv);
char		**unpack_path(t_varenv *varenv);
char		*unpack_pwd(t_varenv *varenv);
char		**redo_env(t_varenv *varenv);
void		revert_pwd(t_varenv *varenv);
void		go_pwd(t_varenv *varenv);
t_varenv	*do_unsetenv(char **args, t_varenv *varenv);
void		do_env(t_varenv *varenv, char **args);
void		do_cd(char **args, t_varenv *varenv);
t_varenv	*stockenv(char **env);
void		letsfree(char **env);
void		print_env(t_varenv *varenv, int izi);
void		errorcd(char *arg);
void		errorhome(char *home);
