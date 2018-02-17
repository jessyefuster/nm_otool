/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessye <jessye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:05:21 by jfuster           #+#    #+#             */
/*   Updated: 2018/02/17 20:06:04 by jessye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

/*
**	Print symbol nodes of the linked-list
**	note : this function handles both 32bit and 64bit symbol
*/
void		print_symbols(char *file, t_symbols	*symbol, uint32_t file_type)
{
	char	type;
	char	**sections;

	sections = get_sections((struct mach_header *)file, file_type);
	while (symbol != NULL)
	{
		type = type_letter(sections, symbol);
		if (F_IS_32(file_type))
		{
			if (symbol->value)
				printf("%08llx %c %s\n", symbol->value, type, symbol->name);
			else
				printf("         %c %s\n", type, symbol->name);
		}
		else
		{
			if (symbol->value)
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
*/
t_symbols	*new_node(uint32_t file_type, void *symbol, char *string_table)
{
	t_symbols	*new;

	if ((new = (t_symbols *)malloc(sizeof(t_symbols))) == NULL) 
		return (NULL);
	new->next = NULL;
	new->name = "bad string index";
	if (F_IS_32(file_type))
	{
		if (!invalid_address(string_table + ((struct nlist *)symbol)->n_un.n_strx))
			new->name = string_table + ((struct nlist *)symbol)->n_un.n_strx;
		new->value = ((struct nlist *)symbol)->n_value;
		new->type = ((struct nlist *)symbol)->n_type;
		new->sect = ((struct nlist *)symbol)->n_sect;
	}
	else
	{
		if (!invalid_address(string_table + ((struct nlist_64 *)symbol)->n_un.n_strx))
			new->name = string_table + ((struct nlist_64 *)symbol)->n_un.n_strx;
		new->value = ((struct nlist_64 *)symbol)->n_value;
		new->type = ((struct nlist_64 *)symbol)->n_type;
		new->sect = ((struct nlist *)symbol)->n_sect;
	}
	return (new);
}