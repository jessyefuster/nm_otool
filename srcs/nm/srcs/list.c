/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:05:21 by jfuster           #+#    #+#             */
/*   Updated: 2018/12/30 17:03:04 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_nm.h"

static void		try_swap_symbol(t_file *file, void *symbol)
{
	if (F_IS_BIG(file->type) && F_IS_32(file->type))
		swap_nlist((struct nlist *)symbol);
	else if (F_IS_BIG(file->type) && F_IS_64(file->type))
		swap_nlist_64((struct nlist_64 *)symbol);
}

/*
**	Create a node with symbol information
**	note : this function handles both 32bit and 64bit symbol
**	note : this function handles endianess
*/

t_symbols		*new_node(t_file *file, void *s, char *st)
{
	t_symbols	*new;

	if ((new = (t_symbols *)malloc(sizeof(t_symbols))) == NULL)
		return (NULL);
	new->next = NULL;
	new->name = "bad string index";
	try_swap_symbol(file, s);
	if (F_IS_32(file->type))
	{
		if (st + ((struct nlist *)s)->n_un.n_strx <= file->ptr + file->size)
			new->name = st + ((struct nlist *)s)->n_un.n_strx;
		new->value = ((struct nlist *)s)->n_value;
		new->type = ((struct nlist *)s)->n_type;
		new->sect = ((struct nlist *)s)->n_sect;
	}
	else
	{
		if (st + ((struct nlist_64 *)s)->n_un.n_strx <= file->ptr + file->size)
			new->name = st + ((struct nlist_64 *)s)->n_un.n_strx;
		new->value = ((struct nlist_64 *)s)->n_value;
		new->type = ((struct nlist_64 *)s)->n_type;
		new->sect = ((struct nlist_64 *)s)->n_sect;
	}
	return (new);
}

/*
**	Add the symbol to the linked-list in ascii order
**	note : this function handles both 32bit and 64bit symbol
**	note : this function handles endianess
*/

enum e_status	store_symbol(t_file *file, t_symbols **symbols, void *symbol,
			char *string_table)
{
	t_symbols		*new;
	t_symbols		*ptr;

	if ((new = new_node(file, symbol, string_table)) == NULL)
		return (program_error("Malloc error", __FILE__, __LINE__));
	ptr = (*symbols);
	if ((*symbols) == NULL || (ft_strcmp(new->name, (*symbols)->name) < 0 ||
	(ft_strcmp(new->name, (*symbols)->name) == 0 &&
	new->value < (*symbols)->value)))
	{
		new->next = (*symbols);
		(*symbols) = new;
	}
	else
	{
		while (ptr->next != NULL &&
		(ft_strcmp(new->name, ptr->next->name) > 0 ||
		(ft_strcmp(new->name, ptr->next->name) == 0 &&
		new->value > ptr->next->value)))
			ptr = ptr->next;
		new->next = ptr->next;
		ptr->next = new;
	}
	return (S_SUCCESS);
}
