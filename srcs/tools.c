/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 11:52:19 by jfuster           #+#    #+#             */
/*   Updated: 2018/04/25 15:41:38 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_nm_otool.h"

enum e_check_result	filecheck_error(char *filename, char *error)
{
	fprintf(stderr, "%s: %s\n", filename, error);
	return (CHECK_BAD);
}

/*
**	TO-DO: Move __FILE__ and __LINE_ to parameters
*/

void				exit_error(char *error)
{
	fprintf(stderr, "EXIT: %s in %s at line %d\n", error, __FILE__, __LINE__);
	exit(EXIT_FAILURE);
}

uint32_t			swap_uint32(uint32_t num)
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

uint64_t			swap_uint64(uint64_t num)
{
	num = (num & 0x00000000FFFFFFFF) << 32u | (num & 0xFFFFFFFF00000000) >> 32u;
	num = (num & 0x0000FFFF0000FFFF) << 16u | (num & 0xFFFF0000FFFF0000) >> 16u;
	num = (num & 0x00FF00FF00FF00FF) << 8u | (num & 0xFF00FF00FF00FF00) >> 8u;
	return (num);
}
