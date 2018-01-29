/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 13:53:06 by jfuster           #+#    #+#             */
/*   Updated: 2015/11/28 13:53:08 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnew(size_t size)
{
	char	*tab;

	tab = (char *)malloc(sizeof(char) * (size + 1));
	if (!tab)
		return (NULL);
	ft_bzero((void *)tab, size + 1);
	return (tab);
}
