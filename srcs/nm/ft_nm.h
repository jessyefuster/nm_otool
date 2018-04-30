/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:12:22 by jfuster           #+#    #+#             */
/*   Updated: 2018/04/30 16:16:13 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H
# include "../ft_nm_otool.h"

/*
**	core.c
*/
enum e_status	handle_macho(t_file *file, t_symbols **symbols);
enum e_status	handle_fat(t_file *file);
enum e_status	handle_archive(t_file *file);

/*
**	list.c
*/
t_symbols		*new_node(t_file *file, void *symbol, char *string_table);
enum e_status	store_symbol(t_file *file, t_symbols **symbols, void *symbol,
				char *string_table);

/*
**	macho.c
*/
enum e_status	store_symbols(t_file *file, struct symtab_command *symtab_cmd,
				t_symbols **symbols);

/*
**	sections.c
*/
char			section_letter(char *segname);
char			**get_sections(struct mach_header *header, t_filetype_t ft);

/*
**	symbols.c
*/
char			type_letter(char **sections, t_symbols *symbol);
enum e_status	print_symbols(t_file *file, t_symbols *ptr);

/*
**	main.c
*/
char			*map_file(char *filename, struct stat *file_info);
enum e_status	nm_if_valid_file(char *filename, bool print_filename);
enum e_status	ft_nm(char *file, char *filename, size_t file_size,
				bool print_filename);

#endif
