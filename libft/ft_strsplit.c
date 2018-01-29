/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 09:39:35 by jfuster           #+#    #+#             */
/*   Updated: 2015/11/30 09:43:26 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	ft_count_words(char const *str, char c)
{
	int		i;
	int		word;
	int		in;

	i = 0;
	in = 0;
	word = 0;
	while (str[i] != '\0')
	{
		if (in && str[i] == c)
			in = 0;
		if (!in && str[i] != c)
		{
			in = 1;
			word++;
		}
		i++;
	}
	return (word);
}

static int	ft_word_len(char const *str, char c)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[i] != c && str[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		n_words;
	int		i;

	n_words = ft_count_words(s, c);
	tab = (char **)malloc(sizeof(char *) * (n_words + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (n_words > 0)
	{
		while (*s == c && *s != '\0')
			s++;
		tab[i] = ft_strsub(s, 0, ft_word_len(s, c));
		s = s + ft_word_len(s, c);
		i++;
		n_words--;
	}
	tab[i] = NULL;
	return (tab);
}
