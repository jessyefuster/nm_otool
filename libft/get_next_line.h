/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 12:06:39 by jfuster           #+#    #+#             */
/*   Updated: 2016/01/22 12:06:42 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "includes/libft.h"
# include <fcntl.h>
# define BUFF_SIZE 32

int		get_next_line(int const fd, char **line);

#endif
