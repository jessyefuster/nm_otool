/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessye <jessye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 11:52:19 by jfuster           #+#    #+#             */
/*   Updated: 2018/03/08 23:36:09 by jessye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

enum status	file_error(char *filename)
{
	fprintf(stderr, "ft_nm: %s: error occured\n", filename);
	return (S_FAILURE);
}

bool		valid_addr(void *ptr)
{
	if ((uint64_t)ptr > g_maxaddr)
		return (FALSE);
	return (TRUE);
}

// void		swap_binary(char *start, size_t size)
// {
// 	uint32_t	*ptr;
// 	void		*end;

// 	end = start + size;
// 	ptr = (uint32_t *)start;
// 	while ((void *)ptr < end)
// 	{
// 		*ptr = swap_uint32(*ptr);
// 		ptr++;
// 	}
// }

uint32_t	swap_uint32(uint32_t num)
{
	uint32_t b0;
	uint32_t b1;
	uint32_t b2;
	uint32_t b3;

	b0 = (num & 0x000000ff) << 24u;
	b1 = (num & 0x0000ff00) << 8u;
	b2 = (num & 0x00ff0000) >> 8u;
	b3 = (num & 0xff000000) >> 24u;
	return (b0 | b1 | b2 | b3);
}

uint64_t	swap_uint64(uint64_t num)
{
	uint32_t b0;
	uint32_t b1;
	uint32_t b2;
	uint32_t b3;
	uint32_t b4;
	uint32_t b5;
	uint32_t b6;
	uint32_t b7;

	b0 = (num & 0x00000000000000ff) << 56u;
	b1 = (num & 0x000000000000ff00) << 44u;
	b2 = (num & 0x0000000000ff0000) << 24u;
	b3 = (num & 0x00000000ff000000) << 8u;
	b4 = (num & 0x000000ff00000000) >> 8u;
	b5 = (num & 0x0000ff0000000000) >> 24u;
	b6 = (num & 0x00ff000000000000) >> 44u;
	b7 = (num & 0xff00000000000000) >> 56u;

	return (b0 | b1 | b2 | b3 | b4 | b5 | b6 | b7);
}

uint32_t	rev_uint32(uint32_t num, t_filetype_t file_type)
{
	if (file_type & F_BIG)
		return (swap_uint32(num));
	return (num);
}

uint64_t	rev_uint64(uint64_t num, t_filetype_t file_type)
{
	if (file_type & F_BIG)
		return (swap_uint64(num));
	return (num);
}

char		section_letter(char *segname)
{
	if (ft_strcmp(segname, "__text") == 0)
		return ('T');
	else if (ft_strcmp(segname, "__data") == 0)
		return ('D');
	else if (ft_strcmp(segname, "__bss") == 0)
		return ('B');
	return ('S');
}

char		type_letter(char **sections, t_symbols *symbol)
{
	char	type_letter;

	type_letter = '?';
	if (symbol->type & N_STAB)
		return ('-');
	else if ((symbol->type & N_TYPE) == N_UNDF)
	{
		type_letter = 'U';
		if (symbol->value)
			type_letter = 'C';
		// if ((symbol->type & N_EXT))
		// 	return (ft_toupper(type_letter));
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
