/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_lint_abs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 17:05:00 by jfuster           #+#    #+#             */
/*   Updated: 2015/11/30 09:31:56 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_putnbr_lint_abs(long n)
{
	char	*str;

	str = ft_ltoa(n);
	if (*str == '-')
		ft_putstr(&str[1]);
	else
		ft_putstr(str);
}
