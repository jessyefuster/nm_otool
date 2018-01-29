/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_toupper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 12:54:57 by jfuster           #+#    #+#             */
/*   Updated: 2015/11/23 13:53:47 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_str_toupper(char *str)
{
	while (*str)
	{
		if (ft_islower(*str))
			*str = ft_toupper(*str);
		str++;
	}
}
