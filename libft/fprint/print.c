/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 14:26:55 by jessyefuster      #+#    #+#             */
/*   Updated: 2019/01/31 16:36:11 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_fprint.h"

void	print_percent(int *flags)
{
	r_align(flags, 1, 1);
	ft_putchar('%');
	l_align(flags, 1);
}

void	print_string(int fd, va_list args, int *flags)
{
	char	*str;
	int		len;

	(void)flags;
	str = va_arg(args, char *);
	len = ft_strlen(str);
	ft_putstr_fd(str, fd);
}

void	print_char(va_list args, int *flags)
{
	int		c;

	c = va_arg(args, int);
	r_align(flags, 1, 1);
	ft_putchar(c);
	l_align(flags, 1);
}

void	print_integer(int fd, va_list args, int *flags)
{
	int		i;

	(void)flags;
	i = va_arg(args, int);
	if (i < 0)
		ft_putchar('-');
	ft_putnbr_fd(i, fd);
}

void	print_hexa(va_list args, char type, int *flags)
{
	uintmax_t	value;
	char		*str;
	int			len;
	int			len_bis;

	value = va_arg(args, uintmax_t);
	if (!flags[CONVERSION])
		value = (unsigned int)value;
	else
		value = convert_uvalue(value, flags[CONVERSION]);
	str = ft_utob(value, 16, "0123456789abcdef");
	if (type == 'X')
		ft_str_toupper(str);
	while (*str == '0' && *(str + 1) != '\0')
		str++;
	len = ft_strlen(str);
	len_bis = flags[PRECISION] > len ? flags[PRECISION] : len;
	len_bis += flags[HASHTAG] ? 2 : 0;
	!flags[ZERO_SPACES] ? r_align(flags, len_bis, flags[PRECISION] > len) : 0;
	if (flags[HASHTAG] && (type == 'x' || type == 'X') && value != 0)
		type == 'x' ? ft_putstr("0x") : ft_putstr("0X");
	flags[ZERO_SPACES] ? r_align(flags, len_bis, flags[PRECISION] > len) : 0;
	print_precision(flags, len);
	ft_putstr(str);
	l_align(flags, len_bis);
}
