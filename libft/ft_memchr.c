/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 15:08:55 by tblanker       #+#    #+#                */
/*   Updated: 2019/11/06 12:55:47 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	char				*result;

	i = 0;
	while (i < n)
	{
		if (((char *)s)[i] == (char)c)
		{
			result = &((char *)s)[i];
			return (result);
		}
		i++;
	}
	return (NULL);
}
