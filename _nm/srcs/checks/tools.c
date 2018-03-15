/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 23:45:46 by jessye            #+#    #+#             */
/*   Updated: 2018/03/09 14:35:17 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_nm.h"

enum check_result		filecheck_error(char *filename, char *error)
{
	fprintf(stderr, "ft_nm: %-50s: %s\n", filename, error);
	return (CHECK_BAD);
}
