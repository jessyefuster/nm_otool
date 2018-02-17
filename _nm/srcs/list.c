/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessye <jessye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:05:21 by jfuster           #+#    #+#             */
/*   Updated: 2018/02/17 01:39:33 by jessye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

/*
**	Print symbol nodes of the linked-list
**	note : this function handles both 32bit and 64bit symbol
**	TODO: type_letter
*/
void		print_symbols(t_symbols	*symbol, uint32_t file_type)
{
	while (symbol != NULL)
	{
		if (F_IS_32(file_type))
		{
			if (symbol->value)
				printf("%08llx  %s\n", symbol->value, symbol->name);
			else
				printf("          %s\n", symbol->name);
		}
		else
		{
			if (symbol->value)
				printf("%016llx  %s\n", symbol->value, symbol->name);
			else
				printf("                  %s\n", symbol->name);
		}
		symbol = symbol->next;
	}
}

/*
**	Create a node with symbol information
**	note : this function handles both 32bit and 64bit symbol
**	TODO: type_letter
*/
t_symbols	*new_node(uint32_t file_type, void *symbol, char *string_table)
{
	t_symbols	*new;

	if ((new = (t_symbols *)malloc(sizeof(t_symbols))) == NULL) 
		return (NULL);
	new->next = NULL;
	new->type_letter = '?';
	if (F_IS_32(file_type))
	{
		new->name = ft_strdup(string_table + ((struct nlist *)symbol)->n_un.n_strx);
		new->value = ((struct nlist *)symbol)->n_value;
		new->type = ((struct nlist *)symbol)->n_type;
	}
	else
	{
		new->name = ft_strdup(string_table + ((struct nlist_64 *)symbol)->n_un.n_strx);
		new->value = ((struct nlist_64 *)symbol)->n_value;
		new->type = ((struct nlist_64 *)symbol)->n_type;
	}
	return (new);
}