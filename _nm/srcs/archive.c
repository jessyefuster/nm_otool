/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:01:25 by jfuster           #+#    #+#             */
/*   Updated: 2018/03/05 16:14:38 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

size_t	*archive_offsets(struct ar_hdr *header)
{
	size_t			i;
	size_t			n_ran;
	uint32_t		rans_size;
	struct ranlib	*ran;

	rans_size = *((uint32_t *)((char *)(header + 1) + ft_atoi((char *)header + 3)));
	n_ran = rans_size / sizeof(struct ranlib);
	ran = (struct ranlib *)((char *)(header + 1) + ft_atoi((char *)header + 3) + sizeof(uint32_t));

	i = 0;
	while (i < n_ran)
	{
		printf("%d\n", ran->ran_off);
		i++;
		ran++;
	}

	return (NULL);
}
