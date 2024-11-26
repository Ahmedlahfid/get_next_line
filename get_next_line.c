/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:21:10 by ahlahfid          #+#    #+#             */
/*   Updated: 2024/11/26 14:14:11 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char *str, char *buffer)
{
	if (buffer)
		free(buffer);
	return (str);
}

static char	*ft_save(char *buffer)
{
	size_t	i;
	char	*left;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (NULL);
	left = ft_strdup(buffer + i + 1);
	if (!left)
		return (NULL);
	return (left);
}

static char	*ft_getline(char *buffer)
{
	size_t	i;
	char	*line;
	size_t	len;

	if (!buffer || !buffer[0])
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	len = i;
	if (buffer[i] == '\n')
		len += 1;
	line = ft_substr(buffer, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

static char	*ft_read(int fd, char *buffer)
{
	char	*buf;
	char	*to_free;
	ssize_t	count;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (ft_free(NULL, buffer));
	count = read(fd, buf, BUFFER_SIZE);
	while (count > 0)
	{
		buf[count] = '\0';
		to_free = buffer;
		buffer = ft_strjoin(buffer, buf);
		free(to_free);
		if (!buffer)
			return (ft_free(NULL, buf));
		if (ft_isnewline(buffer))
			break ;
		count = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	if (count < 0)
		return (ft_free(NULL, buffer));
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 0x7FFFFFFF)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	buffer = ft_read(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_getline(buffer);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	temp = ft_save(buffer);
	free(buffer);
	buffer = temp;
	return (line);
}
