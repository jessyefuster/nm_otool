/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:12:22 by jfuster           #+#    #+#             */
/*   Updated: 2018/04/11 14:24:13 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H
# include "../ft_nm_otool.h"

/*
**	core.c
*/
void				handle_macho(t_file *file, t_symbols **symbols);
void				handle_fat(t_file *file);
void				handle_archive(t_file *file);

/*
**	list.c
*/
void				print_symbols(t_file *file, t_symbols *ptr);
t_symbols			*new_node(t_file *file, void *symbol, char *string_table);

/*
**	macho.c
*/
void				store_symbols(t_file *file, struct symtab_command *symtab_cmd, t_symbols **symbols);

/*
**	sections.c
*/
char				**get_sections(struct mach_header *header, t_filetype_t file_type);

/*
**	sort.c
*/
void				sort_tab(size_t *tab, size_t len);



/*
**	main.c
*/
char				*map_file(char *filename, struct stat *file_info);
enum status			nm_if_valid_file(char *filename, bool print_filename);
enum status			ft_nm(char *file, char *filename, size_t file_size, bool print_filename);

#endif
