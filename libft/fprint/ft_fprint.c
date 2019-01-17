/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessyefuster <jessyefuster@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 13:34:03 by jessyefuster      #+#    #+#             */
/*   Updated: 2019/01/17 13:49:01 by jessyefuster     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_fprint.h"
#include <limits.h>

static void	print_variable(int fd, va_list args, char type, int *flags)
{
	if (type == 's' || type == 'S')
		print_string(fd, args, flags);
	else if (type == 'd')
		print_integer(fd, args, flags);
	else if (type == 'c' && !(flags[CONVERSION] & L))
		print_char(args, flags);
	else if (type == 'x' || type == 'X')
		print_hexa(args, type, flags);
	else if (type == '%')
		print_percent(flags);
}

static char	*parse_option(int fd, va_list args, char *ptr)
{
	int		flags[9];

	ft_bzero(flags, sizeof(int) * 9);
	ptr = check_modifiers(ptr, flags);
	ptr = check_conversions(ptr, flags);
	print_variable(fd, args, *ptr, flags);
	return (ptr + 1);
}

static int	analyse(int fd, va_list args, const char* format)
{
	char	*ptr;
	char	*start;

	ptr = (char *)format;
	start = (char *)format;
	while ((ptr = ft_strchr(ptr, '%')) != NULL)
	{
		ft_putnstr(start, ptr - start);
		ptr = parse_option(fd, args, ptr + 1);
		start = ptr;
	}
	ft_putstr(start);
	return (0);
}

int			ft_fprint(int fd, const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	analyse(fd, args, format);
	va_end(args);
	return (0);
}
