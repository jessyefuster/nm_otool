/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 21:27:26 by jessyefuster      #+#    #+#             */
/*   Updated: 2018/04/13 16:12:37 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_otool.h"

#define I(c) 			((c == CPU_TYPE_I386 || c == CPU_TYPE_X86_64) ? 1 : 4)
#define ADDR_FORMAT(ft)	(F_IS_32(ft) ? "%08llx\t" : "%016llx\t")

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

static void	print_bytes_hexa(t_file *file, void *byte)
{
	cpu_type_t	cpu_type;

	cpu_type = ((struct mach_header *)(file->ptr))->cputype;
	if (cpu_type == CPU_TYPE_I386 || cpu_type == CPU_TYPE_X86_64)
		printf("%02x ", *((unsigned char *)byte));
	else
	{
		if (F_IS_BIG(file->type))
			printf("%08x ", swap_uint32(*((uint32_t *)byte)));
		else
			printf("%08x ", *((uint32_t *)byte));
	}
}

static void	set_variables(void *section, uint64_t *addr, uint64_t *size,
			size_t *offset)
{
	*addr = ((struct section *)section)->addr;
	*size = ((struct section *)section)->size;
	*offset = ((struct section *)section)->offset;
}

static void	set_variables64(void *section, uint64_t *addr, uint64_t *size,
			size_t *offset)
{
	*addr = ((struct section_64 *)section)->addr;
	*size = ((struct section_64 *)section)->size;
	*offset = ((struct section_64 *)section)->offset;
}

void		print_text_section(t_file *file, void *section)
{
	cpu_type_t	c;
	uint64_t	addr;
	uint64_t	size;
	size_t		offset;
	uint64_t	i;

	set_variables64(section, &addr, &size, &offset);
	if (F_IS_32(file->type))
		set_variables(section, &addr, &size, &offset);
	c = ((struct mach_header *)(file->ptr))->cputype;
	i = 0;
	while (i < size)
	{
		if (i % 16 == 0)
		{
			printf(ADDR_FORMAT(file->type), addr);
			addr += 16;
		}
		print_bytes_hexa(file, (void *)file->ptr + offset + i);
		i += I(c);
		if (i == size || (i % 16 == 0))
			printf("\n");
	}
}
