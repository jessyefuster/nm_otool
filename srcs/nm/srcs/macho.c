/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 18:47:30 by jessye            #+#    #+#             */
/*   Updated: 2018/12/19 16:51:08 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_nm.h"

/*
**	Iterate over symbols and store them in SYMBOLS linked-list if valid
**	note : this function handles both 32bit and 64bit arch
**	note : this function handles endianess
*/

enum e_status	store_symbols(t_file *file,
				struct symtab_command *symtab_cmd, t_symbols **symbols)
{
	size_t			i;
	void			*symbol;
	char			*string_table;
	enum e_status	status;

	string_table = file->ptr + symtab_cmd->stroff;
	symbol = file->ptr + symtab_cmd->symoff;
	i = 0;
	while (i < symtab_cmd->nsyms)
	{
		if (F_IS_32(file->type) && !(((struct nlist *)symbol)->n_type & N_STAB))
			status = store_symbol(file, symbols, symbol, string_table);
		else if (F_IS_64(file->type) && !(((struct nlist_64 *)symbol)->n_type &
					N_STAB))
			status = store_symbol(file, symbols, symbol, string_table);
		if (status == S_FAILURE)
			return (S_FAILURE);
		symbol += SYMBOL_SIZE(F_IS_32(file->type));
		i++;
	}
	return (S_SUCCESS);
}
