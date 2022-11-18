/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/07 18:09:11 by cschabra      #+#    #+#                 */
/*   Updated: 2022/11/18 17:32:47 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdbool.h>
#include <limits.h>

static char	*ft_getline(char *store)
{
	char	*ans;
	int		i;

	i = 0;
	while (store[i] && store[i] != '\n')
		i++;
	if (store[i] == '\n')
		i++;
	ans = malloc(sizeof(char) * (i + 1));
	if (!ans)
		return (free(store), NULL);
	ans[i] = '\0';
	i = 0;
	while (store[i] && store[i] != '\n')
	{
		ans[i] = store[i];
		i++;
	}
	if (store[i] == '\n')
		ans[i] = store[i];
	return (ans);
}

static bool	ft_ncheck(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		return (true);
	return (false);
}

static char	*ft_read(char *store, int fd)
{
	char	*buf;
	int		c;

	c = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free(store), NULL);
	buf[0] = '\0';
	while (!(ft_ncheck(buf)) && c != 0)
	{
		c = read(fd, buf, BUFFER_SIZE);
		if (c == 0)
			break ;
		if (c < 0)
			return (free(buf), free(store), NULL);
		while (c <= BUFFER_SIZE)
			buf[c++] = '\0';
		store = ft_strjoin_free(store, buf);
		if (!store)
			return (NULL);
	}
	free(buf);
	return (store);
}

/**
 * @brief Write a function that returns a line read from a
 * file descriptor. Use read malloc and free.
 * 
 * @param fd The file descriptor to read from.
 * @return char* Read line:  correct behavior.
 * NULL: there is nothing else to read, or an error occurred.
 */
char	*get_next_line(int fd)
{
	char		*ans;
	static char	*store;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	if (!store)
	{
		store = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!store)
			return (NULL);
		store[0] = '\0';
	}
	store = ft_read(store, fd);
	if (!store)
		return (NULL);
	ans = ft_getline(store);
	if (!ans)
		return (NULL);
	store = ft_leftover(store);
	if (!store)
		return (free(ans), NULL);
	return (ans);
}

// int	main (void)
// {
// 	char *r;
// 	int fd = open("longline.txt", O_RDONLY);
// 	int i = 1;

// 	// if (fd < 0)
// 	// {
// 	// 	printf("file can't be opened\n");
// 	// 	return 0;
// 	// }

// 	r = "";
// 	while (r)
// 	{
// 		// r = get_next_line(STDIN_FILENO);
// 		r = get_next_line(fd);
// 		printf("%i: %s", i, r);
// 		if (r)
// 			free(r);
// 		i++;
// 		// system("leaks -q a.out");
// 	}
// 	// system("leaks -q a.out");
// 	close(fd);
// 	return (0);
// }