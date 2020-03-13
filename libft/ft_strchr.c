/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 11:54:04 by tblanker       #+#    #+#                */
/*   Updated: 2019/12/04 13:28:53 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char *p;

	while (*s)
	{
		if (s[0] == (char)c)
		{
			p = (char*)s;
			return (p);
		}
		s++;
	}
	if ((char)c == '\0')
		return ((char*)s);
	return (NULL);
}
