/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessyefuster <jessyefuster@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 21:27:26 by jessyefuster      #+#    #+#             */
/*   Updated: 2018/04/10 22:03:35 by jessyefuster     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_otool.h"

void	*get_text_section(t_file *file, void *segment)
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

void	print_text_section(void *section)
{
	(void)section;
	printf("TEXT SECTION HERE\n");
}