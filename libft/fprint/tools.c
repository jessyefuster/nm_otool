/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 13:34:03 by jessyefuster      #+#    #+#             */
/*   Updated: 2019/01/31 15:43:08 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_fprint.h"

void		print_precision(int *modifiers, int len)
{
	int		n_fills;

	if (modifiers[PRECISION_EXISTS] && modifiers[PRECISION] > len)
	{
		n_fills = modifiers[PRECISION] - len;
		while (n_fills > 0)
		{
			ft_putchar('0');
			n_fills--;
		}
	}
}

void		r_align(int *modifiers, int len, int force_space)
{
	char	fill_char;
	int		n_fills;

	fill_char = modifiers[ZERO_SPACES] && force_space == 0 ? '0' : ' ';
	if (modifiers[SPACES] && !modifiers[LEFT_ALIGN])
	{
		n_fills = modifiers[SPACES] - len;
		while (n_fills > 0)
		{
			ft_putchar(fill_char);
			n_fills--;
		}
	}
}

void		l_align(int *modifiers, int len)
{
	char	fill_char;
	int		n_fills;

	fill_char = ' ';
	if (modifiers[SPACES] && modifiers[LEFT_ALIGN])
	{
		n_fills = modifiers[SPACES] - len;
		while (n_fills > 0)
		{
			ft_putchar(fill_char);
			n_fills--;
		}
	}
}

uintmax_t	convert_uvalue(uintmax_t value, int conversions)
{
	if (conversions & L)
		value = (unsigned long)value;
	else if (conversions & LL)
		value = (unsigned long long)value;
	else if (conversions & HH)
		value = (unsigned char)value;
	else if (conversions & H)
		value = (unsigned short)value;
	else if (conversions & Z)
		value = (size_t)value;
	return (value);
}

intmax_t	convert_svalue(intmax_t value, int conversions)
{
	if (conversions & L)
		value = (long)value;
	else if (conversions & LL)
		value = (long long)value;
	else if (conversions & HH)
		value = (char)value;
	else if (conversions & H)
		value = (short)value;
	return (value);
}
