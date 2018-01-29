/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 13:32:54 by jfuster           #+#    #+#             */
/*   Updated: 2015/11/26 14:12:33 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	ft_len_num_unsigned(unsigned long long value, int base)
{
	int		len;

	len = 0;
	while (value / base > 0)
	{
		value /= base;
		len++;
	}
	return (len + 1);
}

char		*ft_utob(unsigned long long value, int base, char *base_str)
{
	char	*str;
	int		len;

	len = ft_len_num_unsigned(value, base);
	str = (char *)malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	len--;
	while (len >= 0)
	{
		str[len] = base_str[value % base];
		value /= base;
		len--;
	}
	return (str);
}
