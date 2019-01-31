/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:05:21 by jfuster           #+#    #+#             */
/*   Updated: 2019/01/31 15:52:11 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_nm.h"

typedef struct mach_header	t_mh;

char			type_letter(char **sections, t_symbols *symbol)
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
	else if ((symbol->type & N_TYPE) == N_SECT)
		type_letter = section_letter(sections[symbol->sect]);
	else
		type_letter = '?';
	if (!(symbol->type & N_EXT))
		type_letter = ft_tolower(type_letter);
	return (type_letter);
}

/*
**	Print symbol nodes of the linked-list
**	note : this function handles both 32bit and 64bit symbol
*/

enum e_status	print_symbols(t_file *file, t_symbols *sym)
{
	char	type;
	char	**sections;

	if ((sections = get_sections((t_mh *)file->ptr, file->type)) == NULL)
		return (program_error("Malloc error", __FILE__, __LINE__));
	while (sym != NULL)
	{
		type = type_letter(sections, sym);
		if (F_IS_32(file->type))
		{
			if (sym->value || type != 'U')
				ft_fprint(1, "%08llx %c %s\n", sym->value, type, sym->name);
			else
				ft_fprint(1, "         %c %s\n", type, sym->name);
		}
		else
		{
			if (sym->value || type != 'U')
				ft_fprint(1, "%016llx %c %s\n", sym->value, type, sym->name);
			else
				ft_fprint(1, "                 %c %s\n", type, sym->name);
		}
		sym = sym->next;
	}
	return (S_SUCCESS);
}
