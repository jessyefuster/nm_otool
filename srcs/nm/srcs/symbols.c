/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:05:21 by jfuster           #+#    #+#             */
/*   Updated: 2018/04/13 16:22:02 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_nm.h"

char		type_letter(char **sections, t_symbols *symbol)
{
	char	type_letter;

	type_letter = ' ';
	if (symbol->type == 0)
		type_letter = '?';
	else if (symbol->type & N_STAB)
		return ('-');
	else if ((symbol->type & N_TYPE) == N_UNDF)
	{
		type_letter = 'U';
		if (symbol->value)
			type_letter = 'C';
	}
	else if ((symbol->type & N_TYPE) == N_ABS)
		type_letter = 'A';
	else if ((symbol->type & N_TYPE) == N_INDR)
		type_letter = 'I';
	else if (symbol->type & N_SECT)
		type_letter = section_letter(sections[symbol->sect]);
	if (!(symbol->type & N_EXT))
		type_letter = ft_tolower(type_letter);
	return (type_letter);
}

/*
**	Print symbol nodes of the linked-list
**	note : this function handles both 32bit and 64bit symbol
*/

void		print_symbols(t_file *file, t_symbols *symbol)
{
	char	type;
	char	**sections;

	sections = get_sections((struct mach_header *)file->ptr, file->type);
	while (symbol != NULL)
	{
		type = type_letter(sections, symbol);
		if (F_IS_32(file->type))
		{
			if (symbol->value || type != 'U')
				printf("%08llx %c %s\n", symbol->value, type, symbol->name);
			else
				printf("         %c %s\n", type, symbol->name);
		}
		else
		{
			if (symbol->value || type != 'U')
				printf("%016llx %c %s\n", symbol->value, type, symbol->name);
			else
				printf("                 %c %s\n", type, symbol->name);
		}
		symbol = symbol->next;
	}
}
