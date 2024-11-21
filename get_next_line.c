/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:21:10 by ahlahfid          #+#    #+#             */
/*   Updated: 2024/11/21 16:38:45 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_save(char *buffer)
{
	size_t	i;
	char	*left;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		return (NULL);
	}
	left = ft_strdup(buffer + i + 1);
	return (left);
}

char	*ft_getline(char *buffer)
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

char	*ft_read(int fd, char *buffer)
{
	char	*buf;
	char	*to_free;
	int		count;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	count = read(fd, buf, BUFFER_SIZE);
	while (count > 0)
	{
		buf[count] = '\0';
		to_free = buffer;
   		buffer = ft_strjoin(buffer, buf);
		free(to_free);
   		if (ft_isnewline(buffer))
			break;
		count = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	if (count < 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char *temp;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 0x7FFFFFFF )
		return (NULL);
	buffer = ft_read(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_getline(buffer);
	temp = ft_save(buffer);
	free(buffer);
	buffer = temp;
	return (line);
}