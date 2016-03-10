/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_nbr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/19 14:11:25 by scaussin          #+#    #+#             */
/*   Updated: 2015/03/25 15:49:42 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbr_tab(const char *s)
{
	int		i;
	int		m;

	i = 0;
	m = 0;
	while (s[i])
	{
		if ((s[i] >= '0' && s[i] <= '9') || s[i] == '-' || s[i] == '+')
		{
			m++;
			while (s[i] == '-' || s[i] == '+')
				i++;
			while ((s[i] >= '0' && s[i] <= '9') && s[i])
				i++;
		}
		if ((s[i] < '0' || s[i] > '9') && s[i] != '-' && s[i] != '+')
			i++;
	}
	return (m);
}

static void	ft_verif(const char *s, int *i, int *k)
{
	while (s[*i] == '-' || s[*i] == '+')
	{
		(*i)++;
		(*k)++;
	}
	while ((s[*i] >= '0' && s[*i] <= '9') && s[*i])
	{
		(*i)++;
		(*k)++;
	}
}

static char	**ft_create_tab(char **split, const char *s, int m)
{
	int				i;
	int				j;
	int				k;
	unsigned int	start;

	i = 0;
	j = 0;
	while (s[i] && m > 0)
	{
		k = 0;
		while ((s[i] < '0' || s[i] > '9') && s[i] != '-' && s[i] != '+' && s[i])
			i++;
		start = i;
		ft_verif(s, &i, &k);
		split[j] = ft_strsub(s, start, k);
		j++;
		m--;
	}
	split[j] = 0;
	return (split);
}

char		**ft_strsplit_nbr(char const *s)
{
	int		m;
	char	**split;

	if (!s || s[0] == '\0')
		return (NULL);
	else
	{
		m = ft_nbr_tab(s);
		split = (char **)malloc((sizeof(char *) * (m + 20)));
		if (split == NULL)
			return (NULL);
		split = ft_create_tab(split, s, m);
		return (split);
	}
}
