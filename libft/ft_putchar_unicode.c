/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_unicode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 12:12:33 by jfuster           #+#    #+#             */
/*   Updated: 2016/04/13 12:12:54 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_putchar_unicode(wchar_t c)
{
	if ((unsigned int)c < 2048)
	{
		ft_putchar(192 | ((unsigned int)c >> 6));
		ft_putchar(128 | ((unsigned int)c & 63));
	}
	else if ((unsigned int)c < 65536)
	{
		ft_putchar(224 | ((unsigned int)c >> 12));
		ft_putchar(128 | (((unsigned int)c >> 6) & 63));
		ft_putchar(128 | ((unsigned int)c & 63));
	}
	else if ((unsigned int)c < 1114112)
	{
		ft_putchar(240 | ((unsigned int)c >> 18));
		ft_putchar(128 | (((unsigned int)c >> 12) & 63));
		ft_putchar(128 | (((unsigned int)c >> 6) & 63));
		ft_putchar(128 | ((unsigned int)c & 63));
	}
}
