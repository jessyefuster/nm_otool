/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:43:44 by jfuster           #+#    #+#             */
/*   Updated: 2018/12/19 17:02:55 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_nm_otool.h"

// static enum e_check_result	check_symbols_32(t_file *file)
// {
// 	return (CHECK_GOOD);
// }

// static enum e_check_result	check_symbols_64(t_file *file)
// {
// 	return (CHECK_GOOD);
// }
static void		try_swap_symbol(t_file *file, void *symbol)
{
	if (F_IS_BIG(file->type) && F_IS_32(file->type))
		swap_nlist((struct nlist *)symbol);
	else if (F_IS_BIG(file->type) && F_IS_64(file->type))
		swap_nlist_64((struct nlist_64 *)symbol);
}

// enum e_check_result			check_symbols(t_file *file)
// {
// 	if (F_IS_32(file->type))
// 		return (check_symbols_32(file));
// 	else
// 		return (check_symbols_64(file));
// }
enum e_check_result			check_symbols(t_file *file, struct symtab_command *st)
{
	size_t			i;
	void			*s;
	char			*string_table;

	string_table = file->ptr + st->stroff;
	s = file->ptr + st->symoff;
	i = 0;
	while (i < st->nsyms)
	{
		try_swap_symbol(file, s);
		if (F_IS_32(file->type))
		{
			if ((char *)(st + ((struct nlist *)s)->n_un.n_strx) > file->ptr + file->size)
				return (filecheck_error(file->name, "symbol index out of file"));
		}
		else
		{
			if ((char *)(st + ((struct nlist_64 *)s)->n_un.n_strx) > file->ptr + file->size)
				return (filecheck_error(file->name, "symbol index out of file"));
		}
		s += SYMBOL_SIZE(F_IS_32(file->type));
		i++;
	}
	return (CHECK_GOOD);
}


