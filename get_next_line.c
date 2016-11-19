/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluder <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 15:57:08 by rluder            #+#    #+#             */
/*   Updated: 2016/01/18 18:56:02 by rluder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			get_buff(int fd, char **data)
{
	char	*temp2;
	char	buf[BUFF_SIZE + 1];
	int		ret2;

	ft_bzero(buf, BUFF_SIZE + 1);
	while (ft_strchr(buf, '\n') == NULL)
	{
		if ((ret2 = read(fd, buf, BUFF_SIZE)) <= 0)
			return (ret2);
		buf[ret2] = '\0';
		if ((temp2 = ft_strjoin(*data, buf)) == NULL)
			return (-1);
		ft_memdel((void**)data);
		*data = temp2;
	}
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	char			*temp;
	char			*ptr;
	int				ret;
	static t_file	file;

	if (file.fd != fd)
	{
		file.fd = fd;
		ft_memdel((void**)&file.data);
	}
	if ((ret = get_buff(fd, &file.data)) == -1)
		return (ret);
	if (file.data == NULL)
		return (0);
	if (ft_strlen(file.data) == 0)
		return (0);
	ptr = ft_strchr(file.data, '\n');
	*line = ft_strndup(file.data, ptr - file.data);
	temp = ft_strsub(file.data, ptr - file.data + 1, ft_strlen(file.data));
	ft_memdel((void**)&file.data);
	file.data = temp;
	return (1);
}
