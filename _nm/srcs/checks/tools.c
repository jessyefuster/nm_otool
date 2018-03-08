/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessye <jessye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 23:45:46 by jessye            #+#    #+#             */
/*   Updated: 2018/03/08 23:46:49 by jessye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_nm.h"

enum check_result		filecheck_error(char *filename, char *error)
{
	fprintf(stderr, "ft_nm: %s: %s\n", filename, error);
	return (CHECK_BAD);
}
