/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 11:58:38 by ylarhris          #+#    #+#             */
/*   Updated: 2023/02/08 08:27:52 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_wdcount(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i + 1] == '\0' || (str[i] == c && str[i + 1] != c))
			count++;
		i++;
	}
	return (count);
}

int	ft_lcount(int i, char *str, char sep)
{
	int	count;

	count = 0;
	while (str[i] == sep)
		i++;
	while (str[i] && str[i] != sep)
	{
		count++;
		i++;
	}
	return (count);
}

char	*ft_filling(char *t__t, char *str, char sep, int i)
{
	int	j;
	int	k;
	int	n;

	j = 0;
	k = 0;
	n = ft_lcount(i, str, sep);
	t__t = (char *) malloc ((n + 1) * sizeof(char));
	if (!t__t)
		return (NULL);
	while (str[i] && k < n)
	{
		t__t [k] = str [i];
		i++;
		k++;
	}
	t__t [k] = '\0';
	return (t__t);
}

void ft_free(char **str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**ft_split(char *str, char sep)
{
	int		i;
	int		j;
	char	**s_str;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	s_str = (char **) malloc ((ft_wdcount(str, sep) + 1) * sizeof(char *));
	if (!s_str)
		return (NULL);
	while (str[i] && j < ft_wdcount(str, sep))
	{
		while (str[i] == sep)
			i++;
		if (str[i] != sep)
		{
			s_str[j] = ft_filling(s_str[j], str, sep, i);
			if(!s_str[j])
				ft_free(s_str);
			j++;
		}
		i += ft_lcount(i, str, sep);
	}
	s_str[j] = NULL;
	return (s_str);
}