/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_macho.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:14:43 by jfuster           #+#    #+#             */
/*   Updated: 2018/03/08 16:34:53 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_nm.h"

t_filetype_t	check_macho(char *file, size_t size, t_filetype_t ft)
{
	(void)file;
	// (void)size;
	if (MACH_HEADER_SIZE(F_IS_32(ft)) > size)
		return (CHECK_BAD);
	return (CHECK_GOOD);
}
