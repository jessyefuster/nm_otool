/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessyefuster <jessyefuster@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 14:08:04 by jessyefuster      #+#    #+#             */
/*   Updated: 2019/01/17 13:46:09 by jessyefuster     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_fprint.h"

bool	is_type(char c)
{
	if (ft_strchr("cCsSdDuUxXoOip%", c))
		return (true);
	return (false);
}

bool	is_modifier(char c)
{
	if (ft_strchr("0123456789-+#. ", c))
		return (true);
	return (false);
}

bool	is_conversion(char c)
{
	if (ft_strchr("lhjz", c))
		return (true);
	return (false);
}

char	*check_modifiers(char *ptr, int *flags)
{
	while (*ptr && is_modifier(*ptr))
	{
		if (*ptr == '0' && ptr++)
			flags[ZERO_SPACES] = 1;
		else if (*ptr == '-' && ptr++)
			flags[LEFT_ALIGN] = 1;
		else if (*ptr == '#' && ptr++)
			flags[HASHTAG] = 1;
		else if (*ptr == '.' && ptr++ && *ptr != '-')
		{
			flags[PRECISION_EXISTS] = 1;
			flags[PRECISION] = ft_atoi(ptr);
			while (ft_isdigit(*ptr))
				ptr++;
		}
		else if (*ptr == '+' && ptr++)
			flags[SHOW_SIGN] = 1;
		else if (*ptr == ' ' && ptr++)
			flags[A_SPACE] = 1;
		else if (ft_isdigit(*ptr))
		{
			flags[SPACES] = ft_atoi(ptr);
			while (ft_isdigit(*ptr))
				ptr++;
		}
		else
			ptr++;
	}
	return (ptr);
}

char	*check_conversions(char *ptr, int *flags)
{
	if (ptr[0] == 'l' && ptr[1] == 'l')
		flags[CONVERSION] = LL;
	else if (ptr[0] == 'l')
		flags[CONVERSION] = L;
	else if (ptr[0] == 'h' && ptr[1] == 'h')
		flags[CONVERSION] = HH;
	else if (ptr[0] == 'h')
		flags[CONVERSION] = H;
	else if (ptr[0] == 'j')
		flags[CONVERSION] = J;
	else if (ptr[0] == 'z')
		flags[CONVERSION] = Z;
	while (is_conversion(*ptr))
		ptr++;
	return (ptr);
}
