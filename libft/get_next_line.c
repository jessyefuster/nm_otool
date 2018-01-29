/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 12:06:23 by jfuster           #+#    #+#             */
/*   Updated: 2016/01/22 12:06:30 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	get_end(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return ('\n');
		i++;
	}
	return ('\0');
}

int		get_next_line(int const fd, char **line)
{
	static char		*save;
	char			buffer[BUFF_SIZE + 1];
	int				ret;

	if (fd < 0)
		return (-1);
	save == NULL ? save = ft_strnew(0) : 0;
	while (!ft_strchr(save, '\n')
		&& (ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		save = ft_strjoin(save, buffer);
	}
	if (ret < 0)
		return (-1);
	if (ret == 0 && ft_strlen(save) == 0)
		return (0);
	(*line) = ft_strsub(save, 0, ft_strchr(save, get_end(save)) - save);
	save = save + ft_strlen((*line)) + 1;
	return (1);
}
