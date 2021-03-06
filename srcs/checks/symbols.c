/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:43:44 by jfuster           #+#    #+#             */
/*   Updated: 2018/12/30 16:34:11 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_nm_otool.h"

static void					try_swap_symbol(t_file *file, void *symbol)
{
	if (F_IS_BIG(file->type) && F_IS_32(file->type))
		swap_nlist((struct nlist *)symbol);
	else if (F_IS_BIG(file->type) && F_IS_64(file->type))
		swap_nlist_64((struct nlist_64 *)symbol);
}

static enum e_check_result	check_symbols_32(t_file *file,
	struct symtab_command *st)
{
	size_t			i;
	void			*s;
	char			*str;

	str = file->ptr + st->stroff;
	s = file->ptr + st->symoff;
	i = 0;
	while (i < st->nsyms)
	{
		try_swap_symbol(file, s);
		if ((char *)(str + ((struct nlist *)s)->n_un.n_strx) >
		file->ptr + file->size)
			return (filecheck_error(file->name, "symbol index out of file"));
		s += SYMBOL_SIZE(F_IS_32(file->type));
		i++;
	}
	return (CHECK_GOOD);
}

static enum e_check_result	check_symbols_64(t_file *file,
	struct symtab_command *st)
{
	size_t			i;
	void			*s;
	char			*str;

	str = file->ptr + st->stroff;
	s = file->ptr + st->symoff;
	i = 0;
	while (i < st->nsyms)
	{
		try_swap_symbol(file, s);
		if ((char *)(str + ((struct nlist_64 *)s)->n_un.n_strx) >
		file->ptr + file->size)
			return (filecheck_error(file->name, "symbol index out of file"));
		s += SYMBOL_SIZE(F_IS_32(file->type));
		i++;
	}
	return (CHECK_GOOD);
}

enum e_check_result			check_symbols(t_file *file,
	struct symtab_command *st)
{
	if (F_IS_32(file->type))
		return (check_symbols_32(file, st));
	else
		return (check_symbols_64(file, st));
}
