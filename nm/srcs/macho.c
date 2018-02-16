/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessye <jessye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 18:47:30 by jessye            #+#    #+#             */
/*   Updated: 2018/02/16 21:58:07 by jessye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

// need to get :
// char		*name;
// uint64_t	value;
// uint8_t		type;
// char		type_letter;
// WIP
static void	store_symbol(uint32_t file_type, t_symbols *symbols, void *symbol, char *string_table)
{
	// uint64_t	value;
	// uint8_t		type;
	struct nlist	*symbol_32;
	struct nlist_64	*symbol_64;

	if (F_IS_32(file_type))
	{
		symbol_32 = (struct nlist *)symbol;
		printf("%08x  %s\n", symbol_32->n_value, string_table + symbol_32->n_un.n_strx);
	}
	else
	{
		symbol_64 = (struct nlist_64 *)symbol;
		printf("%016llx  %s\n", symbol_64->n_value, string_table + symbol_64->n_un.n_strx);
	}
}

/*
**	Iterate over symbols and store them in SYMBOLS chained list if valid
**	note : this function handles both 32bit and 64bit arch
*/
void		store_symbols(char *file, uint32_t file_type, struct symtab_command *symtab_cmd, t_symbols *symbols)
{
	size_t			i;
	void			*symbol;
	char			*string_table;

	string_table = file + symtab_cmd->stroff;
	symbol = file + symtab_cmd->symoff;
	i = 0;
	while (i < symtab_cmd->nsyms)
	{
		if (F_IS_32(file_type) && !(((struct nlist *)symbol)->n_type & N_STAB))
			store_symbol(file_type, symbols, symbol, string_table);
		else if (F_IS_64(file_type) && !(((struct nlist_64 *)symbol)->n_type & N_STAB))
			store_symbol(file_type, symbols, symbol, string_table);
		symbol += SYMBOL_SIZE(F_IS_32(file_type));
		i++;
	}
}
