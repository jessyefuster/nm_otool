/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessye <jessye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:14:43 by jfuster           #+#    #+#             */
/*   Updated: 2018/03/15 21:22:16 by jessye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_nm.h"

enum check_result	check_symtab_command(t_file *file, struct symtab_command *st, t_filetype_t ft)
{
	(void)ft;
	if (st->cmdsize != sizeof(struct symtab_command))
		return (filecheck_error(file->name, "LC_SYMTAB incorrect cmdsize"));
	if (st->symoff > file->size)
		return (filecheck_error(file->name, "LC_SYMTAB symoff out of file"));
	if (st->symoff + st->nsyms * sizeof(struct nlist_64) > file->size)
		return (filecheck_error(file->name, "no size for symbol table"));
	if (st->stroff > file->size)
		return (filecheck_error(file->name, "LC_SYMTAB stroff out of file"));
	if (st->stroff + st->strsize > file->size)
		return (filecheck_error(file->name, "no size for string table"));
	return (CHECK_GOOD);
}

enum check_result	check_macho(t_file *file, t_filetype_t ft)
{

	if (F_IS_32(ft))
		return (check_macho_32(file, ft));
	else
		return (check_macho_64(file, ft));
}
