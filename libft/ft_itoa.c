/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 17:05:00 by jfuster           #+#    #+#             */
/*   Updated: 2018/12/30 16:08:02 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	ft_isnegative(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

static int	ft_len(int n)
{
	int len;

	len = 0;
	if (n == 0)
		len = 1;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	int		len;
	int		sign;
	char	*str;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	sign = ft_isnegative(n);
	if (n < 0)
		n = -n;
	len = ft_len(n);
	len += sign;
	str = (char *)malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	while (len > 0)
	{
		str[len - 1] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	if (sign == 1)
		str[0] = '-';
	return (str);
}
