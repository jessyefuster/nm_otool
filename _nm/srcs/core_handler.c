/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 15:25:04 by jfuster           #+#    #+#             */
/*   Updated: 2018/02/07 16:08:32 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

void		ft_handle_macho(char *file, uint32_t file_type)
{
	if (file_type & F_32)
		ft_handle_macho_32(file);
	else if (file_type & F_64)
		ft_handle_macho_64(file);
}

void		ft_handle_fat(char *file, uint32_t file_type)
{

}

void		ft_handle_archive(char *file, uint32_t file_type)
{

}
