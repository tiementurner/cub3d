/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/18 10:34:06 by tblanker       #+#    #+#                */
/*   Updated: 2020/02/12 10:26:16 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (s[0] == (char)c)
			return (1);
		s++;
	}
	return (0);
}

static	char	*ft_merge(char *p, char const *s1, char const *s2)
{
	int i;
	int j;

	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	j = i;
	i = 0;
	while (s2[i])
	{
		p[j] = s2[i];
		i++;
		j++;
	}
	p[j] = '\0';
	return (p);
}

char			*gnl_strjoin(char *s1, char *s2)
{
	char	*p;

	if (!s1)
		s1 = gnl_strdup("");
	if (!s2 || !s1)
	{
		free(s1);
		return (NULL);
	}
	p = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!p)
	{
		free(s1);
		return (NULL);
	}
	p = ft_merge(p, s1, s2);
	free(s1);
	return (p);
}

size_t			ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

char			*gnl_strdup(char *s1)
{
	char	*p;
	size_t	i;

	if (!s1)
		return (NULL);
	i = 0;
	p = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (p)
	{
		while (i < ft_strlen(s1))
		{
			p[i] = s1[i];
			i++;
		}
		p[ft_strlen(s1)] = '\0';
	}
	return (p);
}
