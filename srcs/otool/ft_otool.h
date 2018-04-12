/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:07:29 by jfuster           #+#    #+#             */
/*   Updated: 2018/04/12 15:10:27 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H
# include "../ft_nm_otool.h"

/*
**	core.c
*/
void		handle_macho(t_file *file);
void		handle_fat(t_file *file);
void		handle_archive(t_file *file);

/*
**	section.c
*/
void		*get_text_section(t_file *file, void *segment);
void		print_text_section(t_file *file, void *section);

/*
**	main.c
*/
// char				*map_file(char *filename, struct stat *file_info);
// enum status			nm_if_valid_file(char *filename, bool print_filename);
enum status		ft_otool(char *ptr, char *filename, size_t file_size);

#endif