/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils_bonus.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/07 18:09:13 by cschabra      #+#    #+#                 */
/*   Updated: 2022/11/18 14:28:34 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_free(char *store, char *buf)
{
	size_t	i;
	size_t	j;
	size_t	slen;
	char	*p;

	i = 0;
	j = 0;
	slen = ft_strlen(store) + ft_strlen(buf);
	p = malloc(sizeof(char) * (slen + 1));
	if (!p)
		return (free(store), free(buf), NULL);
	while (store[i])
	{
		p[i] = store[i];
		i++;
	}
	while (buf[j])
	{
		p[i] = buf[j];
		i++;
		j++;
	}
	free(store);
	p[i] = '\0';
	return (p);
}

char	*ft_leftover(char *store)
{
	int		i;
	int		store_len;
	char	*lo;

	i = 0;
	if (!store[i])
		return (free(store), NULL);
	store_len = ft_strlen(store);
	while (store[i] && store[i] != '\n')
		i++;
	if (store[i] == '\n')
		i++;
	lo = malloc(sizeof(char) * (store_len - i + 1));
	if (!lo)
		return (free(store), NULL);
	store_len = 0;
	while (store[i])
	{
		lo[store_len] = store[i];
		i++;
		store_len++;
	}
	free(store);
	lo[store_len] = '\0';
	return (lo);
}
