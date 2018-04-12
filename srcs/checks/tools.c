/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 23:45:46 by jessye            #+#    #+#             */
/*   Updated: 2018/04/12 15:55:26 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_nm_otool.h"

enum check_result		filecheck_error(char *filename, char *error)
{
	fprintf(stderr, "%-50s: %s\n", filename, error);
	return (CHECK_BAD);
}
