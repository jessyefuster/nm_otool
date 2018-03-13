/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:05:21 by jfuster           #+#    #+#             */
/*   Updated: 2018/03/13 16:39:54 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

/*
**	Print symbol nodes of the linked-list
**	note : this function handles both 32bit and 64bit symbol
*/

void		print_symbols(t_file *file, t_symbols *symbol)
{
	char	type;
	char	**sections;

	sections = get_sections((struct mach_header *)file->ptr, file->file_type);
	while (symbol != NULL)
	{
		type = type_letter(sections, symbol);
		if (F_IS_32(file->file_type))
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

/*
**	Create a node with symbol information
**	note : this function handles both 32bit and 64bit symbol
**	note : this function handles endianess
*/

t_symbols	*new_node(t_file *file, void *symbol, char *string_table)
{
	t_symbols	*new;

	if ((new = (t_symbols *)malloc(sizeof(t_symbols))) == NULL)
		return (NULL);
	new->next = NULL;
	new->name = "bad string index";
	if (F_IS_32(file->file_type))
	{
		if (string_table + S_32(((struct nlist *)symbol)->n_un.n_strx, file->file_type) <= file->ptr + file->size)
			new->name = string_table + S_32(((struct nlist *)symbol)->n_un.n_strx, file->file_type);
		new->value = S_32(((struct nlist *)symbol)->n_value, file->file_type);
		new->type = ((struct nlist *)symbol)->n_type;
		new->sect = ((struct nlist *)symbol)->n_sect;
	}
	else
	{
		if (string_table + S_32(((struct nlist_64 *)symbol)->n_un.n_strx, file->file_type) <= file->ptr + file->size)
			new->name = string_table + S_32(((struct nlist_64 *)symbol)->n_un.n_strx, file->file_type);
		new->value = S_64(((struct nlist_64 *)symbol)->n_value, file->file_type);
		new->type = ((struct nlist_64 *)symbol)->n_type;
		new->sect = ((struct nlist_64 *)symbol)->n_sect;
	}
	return (new);
}
