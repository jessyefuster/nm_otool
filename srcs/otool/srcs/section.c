/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 21:27:26 by jessyefuster      #+#    #+#             */
/*   Updated: 2018/04/11 16:21:23 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_otool.h"

void		*get_text_section(t_file *file, void *segment)
{
	size_t		i;
	size_t		nsects;
	void		*section;

	nsects = ((struct segment_command_64 *)segment)->nsects;
	section = ((struct segment_command_64 *)segment) + 1;
	if (F_IS_32(file->type))
	{
		nsects = ((struct segment_command *)segment)->nsects;
		section = ((struct segment_command *)segment) + 1;
	}
	i = 0;
	while (i < nsects)
	{
		if ((ft_strcmp(((struct section *)section)->segname, "__TEXT") == 0) &&
				(ft_strcmp(((struct section *)section)->sectname, "__text") == 0))
			return (section);
		section += SECTION_SIZE(F_IS_32(file->type));
		i++;
	}
	return (NULL);
}

static void	print_byte_hexa(t_file *file, void *byte, bool newline)
{
	char	final_char;

	final_char = (newline ? '\n': ' ');
	if (F_IS_BIG(file->type))
		printf("%08x%c", *((uint32_t *)byte), final_char);
	else
		printf("%02x%c", *((unsigned char *)byte), final_char);
}

void		print_text_section(t_file *file, void *section)
{
	(void)section;
	uint64_t	addr;
	uint64_t	size;
	size_t		offset;
	uint64_t	i;

	addr = ((struct section_64 *)section)->addr;
	size = ((struct section_64 *)section)->size;
	offset = ((struct section_64 *)section)->offset;
	if (F_IS_32(file->type))
	{
		addr = ((struct section *)section)->addr;
		size = ((struct section *)section)->size;
		offset = ((struct section *)section)->offset;
	}
	i = 0;
	while (i < size)
	{
		if (i % 16 == 0)
		{
			if (F_IS_32(file->type))
				printf("%08llx\t", addr);
			else
				printf("%016llx\t", addr);
			addr += 16;
		}
		print_byte_hexa(file, (void *)file->ptr + offset + i, (bool)((i + 1 == size) || ((i + 1) % 16 == 0)));
		if (F_IS_BIG(file->type))
			i += 3;
		i += 1;
	}
}